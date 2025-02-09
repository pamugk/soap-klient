#! /usr/bin/env bash
packageName="soap-klient"
packageRoot="../src" # Root of translatable sources

#---
echo "[merge] Extracting messages"

xgettext \
    --from-code=UTF-8 \
    --width=400 \
    --add-location=file \
    -C -kde -ci18n -ki18n:1 -ki18nc:1c,2 -ki18np:1,2 -ki18ncp:1c,2,3 -ktr2i18n:1 -kI18N_NOOP:1 \
    -kI18N_NOOP2:1c,2  -kN_:1 -kaliasLocale -kki18n:1 -kki18nc:1c,2 -kki18np:1,2 -kki18ncp:1c,2,3 \
    --package-name="${packageName}" \
    `find "${packageRoot}" -name '*.cpp' -o -name '*.h'` \
    --output="${packageName}.pot.new" \
    || \
    { echo "[merge] error while calling xgettext. aborting."; exit 1; }

sed -i 's/"Content-Type: text\/plain; charset=CHARSET\\n"/"Content-Type: text\/plain; charset=UTF-8\\n"/' "${packageName}.pot.new"
sed -i 's/# SOME DESCRIPTIVE TITLE./'"# Translation of ${packageName} in LANGUAGE"'/' "${packageName}.pot.new"
sed -i 's/# Copyright (C) YEAR THE PACKAGE'"'"'S COPYRIGHT HOLDER/'"# Copyright (C) $(date +%Y)"'/' "${packageName}.pot.new"

if [ -f "${packageName}.pot" ]; then
    newPotDate=`grep "POT-Creation-Date:" "${packageName}.pot.new" | sed 's/.\{3\}$//'`
    oldPotDate=`grep "POT-Creation-Date:" "${packageName}.pot" | sed 's/.\{3\}$//'`
    sed -i 's/'"${newPotDate}"'/'"${oldPotDate}"'/' "${packageName}.pot.new"
    changes=`diff "${packageName}.pot" "${packageName}.pot.new"`
    if [ ! -z "$changes" ]; then
        # There's been changes
        sed -i 's/'"${oldPotDate}"'/'"${newPotDate}"'/' "${packageName}.pot.new"
        mv "${packageName}.pot.new" "${packageName}.pot"

        addedKeys=`echo "$changes" | grep "> msgid" | cut -c 9- | sort`
        removedKeys=`echo "$changes" | grep "< msgid" | cut -c 9- | sort`
        echo ""
        echo "Added Keys:"
        echo "$addedKeys"
        echo ""
        echo "Removed Keys:"
        echo "$removedKeys"
        echo ""

    else
        # No changes
        rm "${packageName}.pot.new"
    fi
else
    mv "${packageName}.pot.new" "${packageName}.pot"
fi

echo "[merge] Done extracting messages"

#---
echo "[merge] Merging messages"
catalogs=`find . -name '*.po' | sort`
for catalog in $catalogs; do
    echo "[merge] $catalog"
    catLocale="$(basename $catalog)"
    msgmerge \
        --width=400 \
        --add-location=file \
        --no-fuzzy-matching \
        --output-file="${catalog}.new" \
        "${catalog}" "${packageName}.pot"
    sed -i "s/# SOME DESCRIPTIVE TITLE./# Translation of ${packageName} in ${catLocale}/" "${catalog}.new"
    sed -i "s/# Translation of ${packageName} in LANGUAGE/# Translation of ${packageName} in ${catLocale}/" "${catalog}.new"
    sed -i 's/# Copyright (C) YEAR THE PACKAGE'"'"'S COPYRIGHT HOLDER/'"# Copyright (C) $(date +%Y)"'/' "${catalog}.new"

    mv "$catalog.new" "$catalog"
done

echo "[merge] Done merging messages"

#---
echo "[merge] Creating new messages"

locales=("ru")
for locale in ${locales[@]}; do
    if [ -f "$locale.po" ]; then
        echo "$locale translation already initialized"
    else
        echo "Initializing $locale translation"

        msginit \
            --input="$packageName.pot" \
            --no-translator --width=400 \
            --locale="$locale" \
            --output-file="$locale.po"
    fi
done

echo "[merge] Done creating new messages"

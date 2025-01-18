#ifndef UI_OPERATIONCALLPAGE_H
#define UI_OPERATIONCALLPAGE_H

#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSplitter>
#include <QTabWidget>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui
{
struct OperationCallPage
{
    QToolButton *sendRequestButton;
    QToolButton *abortRequestButton;
    QLineEdit *urlLineEdit;
    QTextEdit *requestXmlTextEdit;
    QTextEdit *requestRawTextEdit;
    QTextEdit *responseXmlTextEdit;
    QTextEdit *responseRawTextEdit;

    void setupUi(QWidget *implementation)
    {
        implementation->setLayout(new QVBoxLayout(implementation));

        auto pageHeader = new QWidget(implementation);
        pageHeader->setLayout(new QHBoxLayout(pageHeader));
        sendRequestButton = new QToolButton(pageHeader);
        sendRequestButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        pageHeader->layout()->addWidget(sendRequestButton);
        abortRequestButton = new QToolButton(pageHeader);
        abortRequestButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        pageHeader->layout()->addWidget(abortRequestButton);
        urlLineEdit = new QLineEdit(implementation);
        pageHeader->layout()->addWidget(urlLineEdit);
        implementation->layout()->addWidget(pageHeader);

        auto contentSplitter = new QSplitter(implementation);
        const QSize minimumTabSize(200, 200);

        auto requestTabWidget = new QTabWidget(contentSplitter);
        requestTabWidget->setMinimumSize(minimumTabSize);
        requestTabWidget->setTabPosition(QTabWidget::West);
        requestXmlTextEdit = new QTextEdit(requestTabWidget);
        requestTabWidget->addTab(requestXmlTextEdit, i18n("XML"));
        requestRawTextEdit = new QTextEdit(requestTabWidget);
        requestRawTextEdit->setReadOnly(true);
        requestTabWidget->addTab(requestRawTextEdit, i18n("Raw"));
        contentSplitter->addWidget(requestTabWidget);

        auto responseTabWidget = new QTabWidget(contentSplitter);
        requestTabWidget->setMinimumSize(minimumTabSize);
        responseTabWidget->setTabPosition(QTabWidget::West);
        responseXmlTextEdit = new QTextEdit(responseTabWidget);
        responseXmlTextEdit->setReadOnly(true);
        responseTabWidget->addTab(responseXmlTextEdit, i18n("XML"));
        responseRawTextEdit = new QTextEdit(responseTabWidget);
        requestRawTextEdit->setReadOnly(true);
        responseTabWidget->addTab(responseRawTextEdit, i18n("Raw"));
        contentSplitter->addWidget(responseTabWidget);

        contentSplitter->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding));
        implementation->layout()->addWidget(contentSplitter);

#if QT_CONFIG(tooltip)
        sendRequestButton->setToolTip(i18n("Submit request to specified endpoint URL"));
        abortRequestButton->setToolTip(i18n("Abort ongoing request"));
#endif
    }
};
}

#endif // UI_OPERATIONCALLPAGE_H

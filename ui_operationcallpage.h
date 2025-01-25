#ifndef UI_OPERATIONCALLPAGE_H
#define UI_OPERATIONCALLPAGE_H

#include <KLocalizedString>
#include <KTextEdit>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSplitter>
#include <QTabWidget>
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
    KTextEditor::Document *requestXmlDocument;
    KTextEditor::View *requestXmlView;
    KTextEdit *requestRawTextEdit;
    KTextEditor::Document *responseXmlDocument;
    KTextEditor::View *responseXmlView;
    KTextEdit *responseRawTextEdit;

    void setupUi(QWidget *implementation)
    {
        implementation->setLayout(new QVBoxLayout(implementation));

        auto pageHeader = new QWidget(implementation);
        pageHeader->setLayout(new QHBoxLayout(pageHeader));
        sendRequestButton = new QToolButton(pageHeader);
        sendRequestButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        pageHeader->layout()->addWidget(sendRequestButton);
        abortRequestButton = new QToolButton(pageHeader);
        abortRequestButton->setEnabled(false);
        abortRequestButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        pageHeader->layout()->addWidget(abortRequestButton);
        urlLineEdit = new QLineEdit(implementation);
        pageHeader->layout()->addWidget(urlLineEdit);
        implementation->layout()->addWidget(pageHeader);

        auto contentSplitter = new QSplitter(implementation);
        const QSize minimumTabSize(200, 200);
        auto textEditor = KTextEditor::Editor::instance();

        auto requestTabWidget = new QTabWidget(contentSplitter);
        requestTabWidget->setMinimumSize(minimumTabSize);
        requestTabWidget->setTabPosition(QTabWidget::West);
        requestXmlDocument = textEditor->createDocument(implementation);
        requestXmlDocument->setEncoding(QStringLiteral("UTF-8"));
        requestXmlDocument->setMode(QStringLiteral("XML"));
        requestXmlView = requestXmlDocument->createView(contentSplitter);
        requestTabWidget->addTab(requestXmlView, i18n("XML"));
        requestRawTextEdit = new KTextEdit(requestTabWidget);
        requestRawTextEdit->setReadOnly(true);
        requestRawTextEdit->setText(i18n("<missing raw request data>"));
        requestTabWidget->addTab(requestRawTextEdit, i18n("Raw"));
        contentSplitter->addWidget(requestTabWidget);

        auto responseTabWidget = new QTabWidget(contentSplitter);
        requestTabWidget->setMinimumSize(minimumTabSize);
        responseTabWidget->setTabPosition(QTabWidget::West);
        responseXmlDocument = textEditor->createDocument(implementation);
        responseXmlDocument->setEncoding(QStringLiteral("UTF-8"));
        responseXmlDocument->setMode(QStringLiteral("XML"));
        responseXmlDocument->setReadWrite(false);
        responseXmlView = responseXmlDocument->createView(responseTabWidget);
        responseTabWidget->addTab(responseXmlView, i18n("XML"));
        responseRawTextEdit = new KTextEdit(responseTabWidget);
        responseRawTextEdit->setReadOnly(true);
        responseRawTextEdit->setText(i18n("<missing raw response data>"));
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

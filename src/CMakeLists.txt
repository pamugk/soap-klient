add_definitions(
    -DTRANSLATION_DOMAIN=\"soap-klient\"
)

add_executable(soap-klient)

target_sources(soap-klient PRIVATE
    interface.h
    interfacepage.cpp interfacepage.h ui_interfacepage.h
    main.cpp
    mainwindow.cpp mainwindow.h ui_mainwindow.h
    operationcall.h
    operationcallpage.cpp operationcallpage.h ui_operationcallpage.h
    preferences.h
    preferencesdialog.cpp preferencesdialog.h ui_preferencesdialog.h
    project.h
    projectpage.cpp projectpage.h ui_projectpage.h
    soapclient.h soapclient.cpp
    testcase.h
    teststep.h
    testsuite.h
    workspace.h
    workspacemodel.h workspacemodel.cpp
    xmlparser.h xmlparser.cpp
)

target_link_libraries(soap-klient PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
    Qt6::Xml

    KF6::CoreAddons
    KF6::I18n
    KF6::KIOWidgets
    KF6::TextEditor
    KF6::TextWidgets
    KF6::WidgetsAddons
    KF6::XmlGui
)

install(TARGETS soap-klient ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

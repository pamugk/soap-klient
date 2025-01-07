cmake_minimum_required(VERSION 3.20)

project(soap-klient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_MIN_VERSION "6.6.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n KIO WidgetsAddons XmlGui)

add_executable(soap-klient)

target_sources(soap-klient PRIVATE
    main.cpp
    mainwindow.cpp mainwindow.h ui_mainwindow.h
    preferences.h
    preferencesdialog.cpp preferencesdialog.h ui_preferencesdialog.h
    workspace.h
    workspacemodel.h workspacemodel.cpp
    xmlparser.h xmlparser.cpp
)

target_link_libraries(soap-klient PRIVATE
    Qt6::Core
    Qt6::Widgets
    KF6::CoreAddons
    KF6::I18n
    KF6::KIOWidgets
    KF6::WidgetsAddons
    KF6::XmlGui
)

install(TARGETS soap-klient ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

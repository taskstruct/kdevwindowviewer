
set(kdevwindowviewer_PART_SRCS windowcontainer.ui windowcontainer.cpp windowlistmodel.cpp windowlistview.cpp 
    windowviewerplugin.cpp
)

kde4_add_ui_files(kdevwindowviewer_PART_SRCS windowcontainer.ui)

kde4_add_plugin(kdevwindowviewer ${kdevwindowviewer_PART_SRCS})

target_link_libraries(kdevwindowviewer
    ${KDE4_KDEUI_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
)

install(TARGETS kdevwindowviewer DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kdevwindowviewer.desktop DESTINATION ${SERVICES_INSTALL_DIR})

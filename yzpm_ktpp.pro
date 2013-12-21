TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    ../win_includes/vcl\
    ../win_includes/rtl\
    ../win_includes/crtl\
    ../win_includes/sdk\
    ../mylib/Excel\
    ../mylib/SQL\
    common\
    boom_tree\
    boom_tree/contents\
    boom_tree/file_working\
    boom_editor\
    Login\
    Login/dialogs\
    manufacture_schedules\
    manufacture_schedules/reports\
    manufacture_schedules/reports/exsemplars\
    sklad\
    oasu_moover\
    reports\
    professions\
    technology\
    technology/data_classes\
    technology/support_modules\
    technology/support_modules/catalog_workpieces\
    prepare_products_list\
    searcher\
    orders_editor\

SOURCES += \
    ../mylib/Excel/*.cpp \
    ../mylib/SQL/*.cpp \
    *.cpp \
    common/*.cpp \
    boom_tree/*.cpp\
    boom_tree/contents/*.cpp\
    boom_tree/file_working/*.cpp\
    boom_editor/*.cpp\
    Login/*.cpp\
    Login/dialogs/*.cpp\
    manufacture_schedules/*cpp\
    manufacture_schedules/reports/*.cpp\
    manufacture_schedules/reports/exsemplars/*.cpp\
    sklad/*cpp\
    oasu_moover/*cpp\
    reports/*cpp\
    professions/*cpp\
    technology/*cpp\
    technology/data_classes/*cpp\
    technology/support_modules/*cpp\
    technology/support_modules/catalog_workpieces/*cpp\
    prepare_products_list/*.cpp\
    searcher/*cpp\
    orders_editor/*cpp\

HEADERS += \
    ../mylib/Excel/*.h \
    ../mylib/SQL/*.h \
    *.h \
    common/*.h\
    boom_tree/*.h\
    boom_tree/contents/*.h\
    boom_tree/file_working/*.h\
    boom_editor/*.h\
    Login/*.h\
    Login/dialogs/*.h\
    manufacture_schedules/*h\
    manufacture_schedules/reports/*.h\
    manufacture_schedules/reports/exsemplars/*.h\
    sklad/*h\
    oasu_moover/*h\
    reports/*h\
    professions/*h\
    technology/*h\
    technology/data_classes/*h\
    technology/support_modules/*h\
    technology/support_modules/catalog_workpieces/*h\
    prepare_products_list/*.h\
    searcher/*h\
    orders_editor/*h\

OTHER_FILES += \
    *.dfm\
    boom_tree/*.dfm\
    boom_tree/contents/*.dfm\
    boom_tree/file_working/*.dfm\
    boom_editor/*.dfm\
    Login/*.dfm\
    Login/dialogs/*.dfm\
    manufacture_schedules/*dfm\
    sklad/*dfm\
    oasu_moover/*dfm\
    reports/*dfm\
    professions/*dfm\
    technology/*dfm\
    technology/data_classes/*dfm\
    technology/support_modules/*dfm\
    technology/support_modules/catalog_workpieces/*dfm\
    prepare_products_list/*.dfm\
    searcher/*dfm\
    orders_editor/*dfm\

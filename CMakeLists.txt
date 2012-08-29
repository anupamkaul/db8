# @@@LICENSE
#
# Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

cmake_minimum_required(VERSION 2.8.7)

project(db8 CXX)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC2)
webos_component(2 0 0)

include(FindPkgConfig)

# -- check for glib 2.0
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
webos_add_compiler_flags(ALL ${GLIB2_CFLAGS})

# -- check for gthread 2.0
pkg_check_modules(GTHREAD2 REQUIRED gthread-2.0)
webos_add_compiler_flags(ALL ${GTHREAD2_CFLAGS})

# -- check for libxml 2.0
#pkg_check_modules(GXML2 REQUIRED libxml-2.0)
#webos_add_compiler_flags(ALL ${GXML2_CFLAGS})

# -- check for sqlite 3.0
#pkg_check_modules(SQLITE3 REQUIRED sqlite3)
#webos_add_compiler_flags(ALL ${SQLITE3_CFLAGS})

# -- check for cjson
#pkg_check_modules(CJSON REQUIRED cjson)
#include_directories(CJSON_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${CJSON_CFLAGS})

# -- check for mjson
#pkg_check_modules(MJSON REQUIRED mjson)
#include_directories(MJSON_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${MJSON_CFLAGS})

# -- check for pbnjson
#pkg_check_modules(PBNJSON REQUIRED pbnjson)
#include_directories(PBNJSON_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${PBNJSON_CFLAGS})

# -- check for LS2 (internally depends on pmloglib)
pkg_check_modules(LS2 REQUIRED luna-service2)
include_directories(LS2_INCLUDE_DIRS)
webos_add_compiler_flags(ALL ${LS2_CFLAGS})

# -- check for QtCore 
# (e.g. /usr/local/Trolltech/QtLighthouse-4.8.0/lib/pkgconfig/QtCore.pc)
#pkg_check_modules(QTCORE REQUIRED QtCore)
#include_directories(QTCORE_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${QTCORE_CFLAGS})

# -- check for QtGui
# (e.g. /usr/local/Trolltech/QtLighthouse-4.8.0/lib/pkgconfig/QtGui.pc)
#pkg_check_modules(QTGUI REQUIRED QtGui)
#include_directories(QTGUI_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${QTGUI_CFLAGS})

# -- check for uriparser
#pkg_check_modules(URIPARSER REQUIRED uriparser)
#include_directories(URIPARSER_INCLUDE_DIRS)
#webos_add_compiler_flags(ALL ${URIPARSER_CFLAGS})

# -- check for ICU
find_library(ICU NAMES icuuc)
if(ICU STREQUAL "ICU-NOTFOUND")
   message(FATAL_ERROR "Failed to find ICU4C libaries. Please intall.")
endif()

find_library(ICUI18N NAMES icui18n)
if(ICUI18N STREQUAL "ICUI18N-NOTFOUND")
   message(FATAL_ERROR "Failed to find ICU-I18N libaries. Please intall.")
endif()

#webos_build_pkgconfig()
#webos_config_build_doxygen(doc Doxyfile)

# -- no way to disable warn_unused_result right now.
#webos_add_compiler_flags(ALL -g -O2 -Wall -Wno-unused-but-set-variable -Wno-unused-variable -fno-exceptions -fno-rtti -DNDEBUG -fexpensive-optimizations -frename-registers -DMOJ_LINUX -fno-strict-aliasing -DMOJ_INTERNAL -D_REENTRANT)
webos_add_compiler_flags(ALL -g -O2 -Wall -fPIC -Wconversion -Werror -Wno-unused-but-set-variable -Wno-unused-variable -fno-exceptions -fno-rtti -DNDEBUG -fexpensive-optimizations -frename-registers -DMOJ_LINUX -fno-strict-aliasing -DMOJ_INTERNAL -D_REENTRANT)
webos_add_linker_options(ALL --no-undefined)

# -- add local include paths
include_directories(inc)

# -- source for generating libmojocore.so 
file(GLOB CORE_LIB_SOURCES 
        src/core/MojApp.cpp 
        src/core/MojBuffer.cpp 
        src/core/MojDataSerialization.cpp 
        src/core/MojDecimal.cpp 
        src/core/MojEpollReactor.cpp 
        src/core/MojErr.cpp 
        src/core/MojFile.cpp 
        src/core/MojGmainReactor.cpp 
        src/core/MojHashBase.cpp 
        src/core/MojJson.cpp 
        src/core/MojList.cpp 
        src/core/MojLog.cpp 
        src/core/MojLogEngine.cpp 
        src/core/MojMessageDispatcher.cpp 
        src/core/MojObject.cpp 
        src/core/MojObjectBuilder.cpp 
        src/core/MojObjectFilter.cpp 
        src/core/MojObjectSerialization.cpp 
        src/core/MojOs.cpp 
        src/core/MojPmLogAppender.cpp 
        src/core/MojRbTreeBase.cpp 
        src/core/MojRefCount.cpp 
        src/core/MojSchema.cpp 
        src/core/MojService.cpp 
        src/core/MojServiceApp.cpp 
        src/core/MojServiceMessage.cpp 
        src/core/MojServiceRequest.cpp 
        src/core/MojSignal.cpp 
        src/core/MojSock.cpp 
        src/core/MojString.cpp 
        src/core/MojTestRunner.cpp 
        src/core/MojThread.cpp 
        src/core/MojTokenSet.cpp 
        src/core/MojUtil.cpp
        )

# -- source for generating libmojodb.so 
file(GLOB DB_LIB_SOURCES 
        src/db/MojDb.cpp 
        src/db/MojDbAdmin.cpp 
        src/db/MojDbClient.cpp 
        src/db/MojDbCursor.cpp 
        src/db/MojDbExtractor.cpp 
        src/db/MojDbIdGenerator.cpp 
        src/db/MojDbIndex.cpp 
        src/db/MojDbIsamQuery.cpp 
        src/db/MojDbKey.cpp 
        src/db/MojDbKind.cpp 
        src/db/MojDbKindEngine.cpp 
        src/db/MojDbKindState.cpp 
        src/db/MojDbObjectHeader.cpp 
        src/db/MojDbObjectItem.cpp 
        src/db/MojDbPermissionEngine.cpp 
        src/db/MojDbPutHandler.cpp 
        src/db/MojDbQuery.cpp 
        src/db/MojDbQueryFilter.cpp 
        src/db/MojDbQueryPlan.cpp 
        src/db/MojDbQuotaEngine.cpp 
        src/db/MojDbReq.cpp 
        src/db/MojDbRevisionSet.cpp 
        src/db/MojDbSearchCursor.cpp 
        src/db/MojDbServiceClient.cpp 
        src/db/MojDbServiceDefs.cpp 
        src/db/MojDbServiceHandler.cpp 
        src/db/MojDbServiceHandlerBase.cpp 
        src/db/MojDbServiceSchemas.cpp 
        src/db/MojDbStorageEngine.cpp 
        src/db/MojDbTextCollator.cpp 
        src/db/MojDbTextTokenizer.cpp 
        src/db/MojDbTextUtils.cpp 
        src/db/MojDbUtils.cpp 
        src/db/MojDbWatcher.cpp 
        src/db/MojDbServiceHandlerInternal.cpp 
        )

add_library(mojocore SHARED ${CORE_LIB_SOURCES})
target_link_libraries(mojocore 
                      ${GLIB2_LDFLAGS} 
                      ${GTHREAD2_LDFLAGS}
                      ${GXML2_LDFLAGS}
                      ${SQLITE3_LDFLAGS}
                      ${CJSON_LDFLAGS}
                      ${MJSON_LDFLAGS}
                      -L/usr/local/lib;-lpbnjson_c
                      -L/usr/local/lib;-lpbnjson_cpp
                      ${LS2_LDFLAGS}
                      ${QTCORE_LDFLAGS}
                      ${QTGUI_LDFLAGS}
                      ${URIPARSER_LDFLAGS}
                      )
webos_build_library(TARGET mojocore NOHEADERS)

add_library(mojodb SHARED ${DB_LIB_SOURCES})
target_link_libraries(mojodb 
                      ${GLIB2_LDFLAGS} 
                      ${GTHREAD2_LDFLAGS}
                      ${GXML2_LDFLAGS}
                      ${SQLITE3_LDFLAGS}
                      ${CJSON_LDFLAGS}
                      ${MJSON_LDFLAGS}
                      -L/usr/local/lib;-lpbnjson_c
                      -L/usr/local/lib;-lpbnjson_cpp
                      -L/usr/local/lib;-lmojocore
                      ${LS2_LDFLAGS}
                      ${QTCORE_LDFLAGS}
                      ${QTGUI_LDFLAGS}
                      ${URIPARSER_LDFLAGS} 
                      ${ICU}
                      ${ICUI18N}
                      )
webos_build_library(TARGET mojodb NOHEADERS)

# -- source for generating libmojoluna.so 
file(GLOB LUNA_LIB_SOURCES 
        src/luna/MojLunaErr.cpp 
        src/luna/MojLunaMessage.cpp 
        src/luna/MojLunaRequest.cpp 
        src/luna/MojLunaService.cpp
        )

add_library(mojoluna SHARED ${LUNA_LIB_SOURCES})
target_link_libraries(mojoluna 
                      ${GLIB2_LDFLAGS} 
                      ${GTHREAD2_LDFLAGS}
                      ${GXML2_LDFLAGS}
                      ${SQLITE3_LDFLAGS}
                      ${CJSON_LDFLAGS}
                      ${MJSON_LDFLAGS}
                      -L/usr/local/lib;-lpbnjson_c
                      -L/usr/local/lib;-lpbnjson_cpp
                      -L/usr/local/lib;-lmojocore
                      ${LS2_LDFLAGS}
                      ${QTCORE_LDFLAGS}
                      ${QTGUI_LDFLAGS}
                      ${URIPARSER_LDFLAGS} 
                      ${ICU}
                      ${ICUI18N}
                      )
webos_build_library(TARGET mojoluna NOHEADERS)

# -- source for generating mojodb-luna 
file(GLOB LUNA_BIN_SOURCES src/db-luna/MojDbLunaServiceApp.cpp)
file(GLOB BDB_SOURCES 
          src/db-luna/MojDbBerkeleyEngine.cpp 
          src/db-luna/MojDbBerkeleyFactory.cpp 
          src/db-luna/MojDbBerkeleyQuery.cpp
    )

include_directories(/usr/local/BerkeleyDB.4.8/include)
add_executable(mojodb-luna ${LUNA_BIN_SOURCES} ${BDB_SOURCES})
target_link_libraries(mojodb-luna 
                      ${GLIB2_LDFLAGS} 
                      ${GTHREAD2_LDFLAGS}
                      ${GXML2_LDFLAGS}
                      ${SQLITE3_LDFLAGS}
                      ${CJSON_LDFLAGS}
                      ${MJSON_LDFLAGS}
                      -L/usr/local/lib;-lpbnjson_c
                      -L/usr/local/lib;-lpbnjson_cpp
                      mojocore
                      mojodb
                      mojoluna
                      -L/usr/local/BerkeleyDB.4.8/lib;-ldb-4.8 
                      ${LS2_LDFLAGS}
                      ${QTCORE_LDFLAGS}
                      ${QTGUI_LDFLAGS}
                      ${URIPARSER_LDFLAGS} 
                      ${ICU}
                      ${ICUI18N}
                      )

#webos_build_system_bus_files()
webos_build_daemon(NAME mojodb-luna)

#install(FILES files/conf/sysservice-backupkeys.json DESTINATION ${WEBOS_INSTALL_WEBOS_SYSCONFDIR})
#install(FILES files/conf/sysservice.conf DESTINATION ${WEBOS_INSTALL_WEBOS_SYSCONFDIR})
#install(FILES files/sysbus/com.palm.systemservice.backupRegistration.json DESTINATION ${WEBOS_INSTALL_WEBOS_SYSCONFDIR}/backup)


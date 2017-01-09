set(LIBNAME nescore)
set(INCROOT include)
set(SRCROOT src)

set(SRC
	${INCROOT}/basic_types.h
	${INCROOT}/CPU.h
	${SRCROOT}/CPU.cpp
	${INCROOT}/IMemory.h
	${INCROOT}/NESMemory.h
	${SRCROOT}/NESMemory.cpp
	${INCROOT}/ICartridge.h
	${INCROOT}/NROMCartridge.h
	${SRCROOT}/NROMCartridge.cpp
	${INCROOT}/ROMFile.h
	${SRCROOT}/ROMFile.cpp
	${INCROOT}/NESCoreException.h
)

include_directories(${INCROOT})
include_directories(${SRCROOT})

add_library(${LIBNAME} ${SRC})

target_include_directories(${LIBNAME} PUBLIC ${INCROOT})

if(TESTS)
	add_subdirectory(test)
endif()
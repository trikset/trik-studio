defineTest(links) {
    LIBS *= -L$$GLOBAL_DESTDIR
    LIBS *= -L$$DESTDIR
    PROJECTS = $$1

    for(PROJECT, PROJECTS) {
        contains(PROJECT, .*QsLog.*) {
            LIBS += -ltrikQsLog$$CONFIGURATION_SUFFIX
        } else {
	        LIBS += -l$$PROJECT$$CONFIGURATION_SUFFIX
	    }
    }
    export(LIBS)
}

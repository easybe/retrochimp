#include "Processes.r"

resource 'SIZE' (-1) {
    dontSaveScreen,
    acceptSuspendResumeEvents,
    enableOptionSwitch,
    canBackground,
    multiFinderAware,
    backgroundAndForeground,
    dontGetFrontClicks,
    ignoreChildDiedEvents,
    is32BitCompatible,
    isHighLevelEventAware,
    onlyLocalHLEvents,
    notStationeryAware,
    reserved,
    reserved,
    reserved,
    reserved,
#ifdef TARGET_API_MAC_CARBON
    500 * 1024, // Carbon apparently needs additional memory.
    500 * 1024
#else
    100 * 1024,
    100 * 1024
#endif
};

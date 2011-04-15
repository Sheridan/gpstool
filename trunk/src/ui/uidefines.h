#ifndef __UIDEFINES_H__
#define __UIDEFINES_H__

#include "st.h"

#define GT_SAVE_DIALOG_STATE(_name) \
    { \
        GT_OPTIONS_APP->setDialogState(_name, options::SDialogState(pos(), size())); \
    }

#define GT_RESTORE_DIALOG_STATE(_name) \
    { \
        options::SDialogState state = GT_OPTIONS_APP->getDialogState(_name); \
        resize(state.size); \
        move(state.position); \
    }

#endif // __UIDEFINES_H__

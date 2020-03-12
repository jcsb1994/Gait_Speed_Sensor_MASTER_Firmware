#include "functions_config.h"

/* Create functions to link to your tact instances here */

// Up button

void up_r()
{
  myMenu.moveCursor(DOWN);
}

void up_h()
{
}

// Select Button

void sel_r()
{
  myFSM.setEvent(events::select);
}

void sel_h()
{
}

// Down button

void down_r()
{
  myMenu.moveCursor(UP);
}

void down_h()
{
}

// Left Button

void left_r()
{
  myFSM.setEvent(events::decrement);
}

void left_h()
{
  myFSM.setEvent(events::back);
}

// Right Button

void ri_r()
{
  myFSM.setEvent(events::increment);
}

void ri_h()
{
}
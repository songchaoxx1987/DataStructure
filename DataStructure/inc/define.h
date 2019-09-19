#pragma once
#define SAFE_DELETE(p) if (p) {delete p; p = NULL;}
#define _EH 0
#define _LH 1
#define _RH -1
#include "Master.h"
#include "bass.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void CreateFileHeader(HSTREAM stream);
void SaveFile(WSABUF buffer);
void StopSaveFile();
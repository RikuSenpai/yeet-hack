#pragma once

template <typename T>
T CallVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}
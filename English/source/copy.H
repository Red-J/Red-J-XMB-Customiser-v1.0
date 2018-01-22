/*
UnEnTete.h
*/
 
/* Code pour éviter les erreurs quand on inclue deux fois le fichier */
#ifndef H_FILES
#define H_FILES


 #ifdef __cplusplus
extern "C" {
#endif



int CopyFile(const char* path, const char* path2);

#ifdef __cplusplus
}
#endif
 
#endif /* H_FILES*/

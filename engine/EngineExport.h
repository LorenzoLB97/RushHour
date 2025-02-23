/**
 * @file EngineExport.h
 * @brief Definizione di macro per l'esportazione e l'importazione di simboli di libreria dinamica.
 *
 * Questo file definisce macro che gestiscono l'esportazione e l'importazione di simboli
 * quando si utilizzano librerie dinamiche, particolarmente su piattaforma Windows.
 */
#ifndef ENGINE_EXPORT_H
#define ENGINE_EXPORT_H

 // Needed so we can use the marked classes from outside engine

#ifdef _WINDOWS 	
#ifdef ENGINE_EXPORTS
#define LIB_API __declspec(dllexport) ///< Macro per l'esportazione di simboli dalla libreria dinamica.
#else
#define LIB_API __declspec(dllimport) ///< Macro per l'importazione di simboli dalla libreria dinamica.
#endif      	
#else 
#define LIB_API  ///< Definizione vuota per altre piattaforme.
#endif

#endif // ENGINE_EXPORT_H

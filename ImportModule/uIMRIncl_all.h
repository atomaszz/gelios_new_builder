//---------------------------------------------------------------------------

#ifndef uIMRIncl_allH
#define uIMRIncl_allH

//#include "types.h"

//---------------------------------------------------------------------------
//значения для типов блоков
#define RAB         1  //рабоч
#define RAB_FAKE       12  //рабоч фиктивная
#define RAB_POSL       13  //послед рабоч
#define RAB_2par_AND 2 // парал И
#define RAB_2par_OR  3 // парал ИЛИ
#define DIAGN       4  //  диагност РО-ДК
#define DIAGN_2     5  //  функцио контр РО-ФК
#define RASV        6  //  развилк ДК - "1 - РО1 "0 - РО2
#define PROV_IF     7  //  контроль работосп (с предусловием) ДК "0 - РО
#define WHILE_DO    8  // контр работ с постусловием РО - ДК "0 - РО
#define WHILE_DO_2  9999  //   ФК с постусловием (не применяется)
#define DO_UNTIL    109999 //  контроль Работспос как 7
#define DO_UNTIL_2  119999 //     ФК как 5
#define DO_WHILE_DO 9 //  ДК с востановл работосп РО1 ДК РО2
#define DO_WHILE_DO_2 10 // ФК с доработкой РО1 - ФК - РО2
#define RASV_SIM    11  // развилка для альтернативных подмножеств

//значения признака открытого файла
#define NO_OPEN  0    //нет открытого файла
#define YES_OPEN 1    //есть открытый файл (не измененный)
#define YES_OPEN_MOD 2//есть открытый файл (измененный)

#define YES_TABLE 1  //признаки наличия таблицы
#define NO_TABLE  0

#define RADIUS 20 //отклонение от центра ТФЕ при определении попадания мыши

#define FNULL -1L //обозначение нуля в файле
#define BEGIN 4L  //указатель на начало данных в файле

#define CFG_NAME "graphtfe.cfg" //имя файла-конфигурации, в нашем случае
                                //набор имен файлов, созданных в процессе работы

#define DEC_ARH "arhive.arh" //имя файла, хранящего архив решений

#define PROP  0 //для настройки типа характеристик
#define FUZZY 1

#define WIN  0 //для настройки типа кодировки
#define DOS 1

#define BLOCK  0 //для настройки типа оптимизации
#define UROV 1

#define TOHN  0 //для настройки метода оптимизации (точный или приближ.)
#define PRIBLJ1 1
#define PRIBLJ2 2

//константы для определения типа выбранной задачи оптимизации
#define ZAD_1 0
#define ZAD_2 1
#define ZAD_3 2
#define ZAD_4 3
#define ZAD_5 4
#define ZAD_6 5
#define NONE  6

//типы элементов
#define SIMP 0 //простой
#define COMP 1 //составной

//типы типовых операций
#define LABOUR   0 //рабочая
#define CONTROL  1 //КР
#define FUNCTION 2 //КФ
#define PROVERKA 3 //Проверка

#define LABOUR_T   "rab" //рабочая
#define CONTROL_T  "cont" //КР
#define FUNCTION_T "func" //КФ
#define PROVERKA_T "prov" //Проверка

#define BB  1
#define BT  2
#define BV  3
#define BTV 4
#define BBS 5
#define BTS 6
#define BVS 7
#define BTVS 8

#endif

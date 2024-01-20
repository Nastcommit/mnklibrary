# mnklibrary
В репозитории добавлены структурные файлы библиотеки, также добавлен
make файл.

Сборка исполняемого файла mnkmain, его запуск, после этого 
удаляются объектные файлы, созданные на этапе сборки:
- make -f MakeFile mnkmain start deleteobj

Сборка исполняемого файла mnk-statmain статической библиотеки и его запуск:
- g++ ./MNKex.cxx -L. -lmnk -o mnk-statmain
- ./mnk-statmain

Сборка исполняемого файла MNKex-dinamic динамической библиотеки:
- g++ ./MNKex.cxx -L/home/anastasia/mylib -lmnk -o MNKex-dinamic 
# /home/anastasia/mylib-путь к каталогу с динамической библиотекой
Перед запуском файла следует модифицировать переменную окружения
LD_LIBRARY_PATH:
- LD_LIBRARY_PATH=/home/anastasia/mylib
Запуск исполняемого файла:
- ./MNKex-dinamic

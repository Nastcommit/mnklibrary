Здесь представлены статические и динамические библиотеки для подбора параметров экспериментальной зависимости методом
наименьших квадратов.
Сборка исполняемого файла mnk-statmain статической библиотеки и его запуск:
    • g++ ./MNKex.cxx -L. -lmnk -o mnk-statmain 
    • ./mnk-statmain 
Сборка исполняемого файла MNKex-dinamic динамической библиотеки:
    • g++ ./MNKex.cxx -L/home/anastasia/mylib -lmnk -o MNKex-dinamic 
Файл student -файл, в котром находится таблица Стьюдента.
А также представлен make файл,который предназначен для автоматизации сборки наших библиотек из исходного кода.
Сборка исполняемого файла mnkmain, его запуск, после этого удаляются объектные файлы, созданные на этапе сборки:
    • make -f MakeFile mnkmain start deleteobj 
Перед запуском файла следует модифицировать переменную окружения LD_LIBRARY_PATH:
    • LD_LIBRARY_PATH=/home/user/mylib Запуск исполняемого файла: 
    • ./MNKex-dinamic 
Где /home/user/mylib -путь к каталогу с динамической библиотекой.

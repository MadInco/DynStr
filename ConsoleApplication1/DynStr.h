//DynStr - like "Dynamic String" от LSS.
//Решение тестового задания для Targem Games.
//По хорошему, описание прототипов вывести в отдельный файл, но и так работает))).
#define uint unsigned int
class DynStr {
private:
    char* stroka;
    uint length;//Длина строки без 0-символа
    bool isErased = false;
    //Заменяет n символов str на smb. Если n больше длины, то n=длина
    static void strsmb(char* str, char smb = '\0', int n = -1) {
        int len;
        len = strlen(str);
        if (n != -1 && n <= len)
            len = n;
        while (len>=0) {
            str[len] = smb;
            len--;
        }
    }
    //Длина символьной константной строки без 0-символа
    static uint strlen(const char* str)    {
        uint length = 0;
        while (*str++)
            ++length;
        return(length);
    }
    //Копирует содержимое src в dest посимвольно
    static char* strcpy(char* dst, const char* src){
        char* cp = dst;
        while (*cp++ = *src++)/* Copy src over dst */
            ;
        *--cp = '\0';
        return (dst);
    }
    //Вставка src в конец dest(аналог конкатенации)
    static char* strcat(char* dst, const char* src){
        char* cp = dst;
        while (*cp++)
            ;
        *cp--;
        while (*src){
            *cp++ = *src++;
        }
        *cp = '\0';
        return (dst);
    }
    //Перевод символов src в нижний регистр
    static char* strlow(const char* src){
        uint lenS = strlen(src);
        uint len0 = lenS + 1;
        char* ret = new char[len0];
        uint i;
        for (i = 0; i < len0; i++) {
            if (src[i] >= 65 && src[i] <= 91)
                ret[i] = (int)src[i] + 32;
            else
                ret[i] = src[i];
        }
        ret[lenS] = '\0';
        return ret;
    }
    //Статическая функция  для операторов сравнения.Принимает на вход два набора символов.
    //От слов Less,Equal,Great
    //Возвращает -1, если первая строка меньше другой по алфавиту(Лексикографический), 0 - равны, 1 - первая больше другой по алфавиту
    static int _LEG(const char* str1, const char* str2) {
        int ret = 0;
        char* op1 = strlow(str1);
        char* op2 = strlow(str2);
        char* c1 = op1;
        char* c2 = op2;
        while (!(ret = *c1 - *c2) && *c2)
            ++c1, ++c2;
        if (ret < 0)
            ret = -1;
        else if (ret > 0)
            ret = 1;
        delete[] op1;//here check
        delete[] op2;
        return(ret);
    }
public:    
    //Конструктор по размеру
    DynStr(uint size = 0) {
        length = size ;
        uint len0 = size + 1;
        stroka = new char[len0];//Скорее всего, здесь будет мусор
        stroka[length] = '\0';
    }
    //Конструктор копирования 
    DynStr(char* str1) {
        length =  strlen(str1);
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka, str1);
    }
    //Конструктор копирования константный
    DynStr(const char* str1) {
        length = strlen(str1);
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka, str1);
    }
    //Конструктор копирования 
    DynStr(DynStr& d) {
        length =  strlen(d.stroka);
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka, d.stroka);
    }
    //Конструктор копирования константный
    DynStr(const DynStr& d) {
        uint len0 = d.length + 1;
        stroka = new char[len0];
        length = d.length;
        //stroka[length] = '\0';
        strcpy(stroka, d.stroka);
    }
    //Конструктор перемещения
    DynStr(DynStr&& dMove) noexcept{
       length = dMove.length;
       uint len0 = length + 1;
       stroka = new char[len0];
       //stroka[length] = '\0';
       strcpy(stroka, dMove.getStr());
       dMove.~DynStr();
    }
    virtual ~DynStr() {
        if (!isErased){
            if (stroka != nullptr) {
                delete[] stroka;
                isErased = true;
            }
        }
    }
    //оператор присваивание копирования
    DynStr& operator = (DynStr& d) {
        if (&d == this)
            return *this;
        if (stroka)
            delete[] stroka;
        length = d.length;
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka,d.stroka);
        return *this;
    }
    //оператор присваивание копирования
    DynStr& operator = (char* d) {
        if (d == getStr())
            return *this;
        if (stroka)//stroka
            delete[] stroka;
        length = strlen(d);
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka, d);
        return *this;
    }
    //оператор присваивание перемещения
    DynStr& operator = (DynStr&& dMove) noexcept {
        if (&dMove == this)
            return *this;
        if (stroka)
            delete[] stroka;
        length = dMove.length;
        uint len0 = length + 1;
        stroka = new char[len0];
        //stroka[length] = '\0';
        strcpy(stroka, dMove.getStr());
        dMove.~DynStr();
        return *this;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this < d1
    bool operator < (DynStr d1) const {
        int ret = _LEG(this->stroka,d1.getStr());
        if (ret == -1)
            return true;
        return false;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this > d1
    bool operator > (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret == 1)
            return true;
        return false;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this >= d1
    bool operator >= (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret >= 0)
            return true;
        return false;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this <= d1
    bool operator <= (DynStr d1)  const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret <= 0)
            return true;
        return false;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this == d1
    bool operator == (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret == 0)
            return true;
        return false;
    }
    //Сравнивает первый операнд со вторым
    //Использует статическую функцию LEG()
    //this != d1
    bool operator != (const DynStr d1) const {
        if (*this == d1)
            return false;
        return true;
    }
    //"Внешний" оператор сложения(конкатенации) строк
    //Описание прототипов выведено за пределы класса
    friend DynStr operator + (DynStr& d1, DynStr& d2);
    friend DynStr operator + (DynStr&& d1, DynStr&& d2);

    //Статическая публичная функция для константных строк.Принимает на вход два набора символов.
    //От слов Less,Equal,Great
    //Возвращает -1, если первая строка меньше другой по алфавиту(Лексикографический), 0 - равны, 1 - первая больше другой по алфавиту
    static int LEG(const char* str1, const char* str2) {
        return _LEG(str1,str2);
    }
    //Выводит содержимое строки
    const char* getStr() {
         return stroka;
    };
    //Выводит длину строки из поля
    const uint getLength() {
          return length;
    }
    //Статическая публичная функция 
    //Длина символьной строки
    static uint strlen(char* str) {
      return strlen((const char*)str);
    }
};

DynStr operator + (DynStr& d1, DynStr& d2) {
    char* strRet;
    uint len0 = d1.getLength() + d2.getLength() + 1;
    strRet = new char[len0];
    DynStr::strcpy(strRet, d1.getStr());
    DynStr::strcat(strRet, d2.getStr());
    DynStr ret(strRet);
    delete[] strRet;
    return ret;
};
DynStr operator + (DynStr&& d1, DynStr&& d2) {
    char* strRet;
    uint len0 = d1.getLength() + d2.getLength() + 1;
    strRet = new char[len0];
    DynStr::strcpy(strRet, d1.getStr());
    DynStr::strcat(strRet, d2.getStr());
    DynStr ret(strRet);
    delete[] strRet;
    d1.~DynStr();
    d2.~DynStr();
    return ret;
};
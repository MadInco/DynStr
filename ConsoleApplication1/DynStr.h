//DynStr - like "Dynamic String" �� LSS.
//������� ��������� ������� ��� Targem Games.
//�� ��������, �������� ���������� ������� � ��������� ����, �� � ��� ��������))).
#define uint unsigned int
class DynStr {
private:
    char* stroka;
    uint length;//����� ������ ��� 0-�������
    
    //�������� n �������� str �� smb. ���� n ������ �����, �� n=�����
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
    //����� ���������� ����������� ������ ��� 0-�������
    static uint _strlen(const char* str)    {
        uint length = 0;
        while (*str++)
            ++length;
        return(length);
    }
    //�������� ���������� src � dest �����������
    static char* strcpy(char* dst, const char* src){
        char* cp = dst;
        while (*cp++ = *src++)/* Copy src over dst */
            ;
        *--cp = '\0';
        return (dst);
    }
    //������� src � ����� dest(������ ������������)
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
    //������� �������� src � ������ �������
    static void strlow(const char* src, char * dst){
        uint lenS = _strlen(src);
        uint len0 = lenS + 1;        
        char* ret = dst;

        for (uint i = 0; i < len0; i++) {
            if (src[i] >= 65 && src[i] <= 91)
                ret[i] = (int)src[i] + 32;
            else
                ret[i] = src[i];
        }
        ret[lenS] = '\0';
    }
    //����������� �������  ��� ���������� ���������.��������� �� ���� ��� ������ ��������.
    //�� ���� Less,Equal,Great
    //���������� -1, ���� ������ ������ ������ ������ �� ��������(������������������), 0 - �����, 1 - ������ ������ ������ �� ��������
    static int _LEG(const char* str1, const char* str2) {
        int ret = 0;
        char* op1 = new char[_strlen(str1) + 1];
        char* op2 = new char[_strlen(str2) + 1];
        strlow(str1, op1);
        strlow(str2, op2);
        char* c1 = op1;
        char* c2 = op2;

        while (!(ret = *c1 - *c2) && *c2)
            ++c1, ++c2;
        if (ret < 0)
            ret = -1;
        else if (ret > 0)
            ret = 1;
        delete[] op1;
        delete[] op2;
        return(ret);
    }
public:    
    //����������� �� �������
    DynStr(uint size = 0) {
        length = size ;
        uint len0 = size + 1;
        stroka = new char[len0];//������ �����, ����� ����� �����
        stroka[length] = '\0';
    }
    //����������� ����������� �����������
    DynStr(const char* str1) {
        length = _strlen(str1);
        uint len0 = length + 1;
        stroka = new char[len0];
        strcpy(stroka, str1);
    }
    //����������� ����������� �����������
    DynStr(const DynStr& d) {
        uint len0 = d.length + 1;
        stroka = new char[len0];
        length = d.length;
        strcpy(stroka, d.stroka);
    }
    //����������� �����������
    DynStr(DynStr&& dMove) noexcept{
       length = dMove.length;
       uint len0 = length + 1;
       stroka = new char[len0];
       strcpy(stroka, dMove.getStr());
    }
    virtual ~DynStr() {
            if (stroka != nullptr) {
                delete[] stroka;
        }
    }
    //�������� ������������ �����������
    DynStr& operator = (DynStr& d) {
        if (&d == this)
            return *this;
        if (stroka)
            delete[] stroka;
        length = d.length;
        uint len0 = length + 1;
        stroka = new char[len0];
        strcpy(stroka,d.stroka);
        return *this;
    }
    //�������� ������������ �����������
    DynStr& operator = (DynStr&& dMove) noexcept {
        if (&dMove == this)
            return *this;
        if (stroka)
            delete[] stroka;
        length = dMove.length;
        uint len0 = length + 1;
        stroka = new char[len0];
        strcpy(stroka, dMove.getStr());
        return *this;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this < d1
    bool operator < (DynStr d1) const {
        int ret = _LEG(this->stroka,d1.getStr());
        if (ret == -1)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this > d1
    bool operator > (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret == 1)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this >= d1
    bool operator >= (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret >= 0)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this <= d1
    bool operator <= (DynStr d1)  const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret <= 0)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this == d1
    bool operator == (DynStr d1) const {
        int ret = _LEG(this->stroka, d1.getStr());
        if (ret == 0)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this != d1
    bool operator != (const DynStr d1) const {
        if (*this == d1)
            return false;
        return true;
    }
    //"�������" �������� ��������(������������) �����
    //�������� ���������� �������� �� ������� ������
    friend DynStr operator + (DynStr& d1, DynStr& d2);
    friend DynStr operator + (DynStr&& d1, DynStr&& d2);

    //����������� ��������� ������� ��� ����������� �����.��������� �� ���� ��� ������ ��������.
    //�� ���� Less,Equal,Great
    //���������� -1, ���� ������ ������ ������ ������ �� ��������(������������������), 0 - �����, 1 - ������ ������ ������ �� ��������
    static int LEG(const char* str1, const char* str2) {
        return _LEG(str1,str2);
    }
    //������� ���������� ������
    const char* getStr() {
         return stroka;
    };
    //������� ����� ������ �� ����
    const uint getLength() {
          return length;
    }
    //����������� ��������� ������� 
    //����� ���������� ������
    static uint strlen(char* str) {
      return _strlen((const char*)str);
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
    return ret;
};
#pragma once
//DynStr - like "Dynamic String" �� LSS.
//������� ��������� ������� ��� Targem Games.
//�� ��������, �������� ���������� ������� � ��������� ����, �� � ��� ��������))).
class DynStr {
private:
    char* stroka;
    unsigned int length;

    //����� ���������� ������
    static int strlen(char* str) {
        int i;
        for (i = 0; *str++; i++);
            return i;
    }
    //����� ���������� ����������� ������
    static int strlen(const char* str) {
        return strlen((char*)str);
    }
    //�������� ���������� src � dest �����������, ���� ���� �� ��������
    //������� �������, �� ������ ���������� �����.
    static void strcpy(char * dest, char * src) {
        int lenD = strlen(dest);
        int lenS = strlen(src);
        int len = (lenD < lenS ? lenD : lenS);
        for (int i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest[len] ='\0';
    }
    //������� src � ����� dest(������ ������������)
    static void strcat(char* dest, char* src) {
        int lenD = strlen(dest);
        int lenS = strlen(src);
        int len = lenD + lenS;
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (i >= lenD)
              dest[i] = src[j++];
        }
        dest[len] = '\0';
    }
    //������� �������� src � ������ �������
    static char* strlow(char* src) {
        int lenS = strlen(src);
        char* ret = new char[lenS+1];
        int i;
        for (i = 0; i < lenS; i++) {
            if (src[i] >= 65 && src[i] <= 91)
                ret[i] = (int)src[i] + 32;
            else
                ret[i] = src[i];
        }
        ret[i] = '\0';
        return ret;
    }
    //����������� �������  ��� ���������� ���������.��������� �� ���� ��� ������ ��������.
    //�� ���� Less,Equal,Great
    //���������� -1, ���� ������ ������ ������ ������ �� ��������(������������������), 0 - �����, 1 - ������ ������ ������ �� ��������
    static int LEG(char* str1,char* str2) {
        int lenT = strlen(str1);
        int lenD = strlen(str2);
        int cmp_len = lenT- lenD;
        if (cmp_len < 0)
            cmp_len *= -1;
        int cmp = 0;
        int len = (lenT < lenD ? lenT : lenD);
        char* op1 = strlow(str1);
        char* op2 = strlow(str2);
        int ret = 0;
        for (int i = 0; i < len + cmp_len; i++) {
            if(i>=len){
                i = len + cmp_len;
                if (len == lenT)//"str1" is longer
                    ret = -1;
                else
                    ret = 1;//"str2" is longer
            }
            else {
                cmp = ((int)op1[i] - (int)op2[i]);
                if (cmp < 0) {
                    i = len + cmp_len;
                    ret = -1;
                }
                else if (cmp > 0) {
                    i = len + cmp_len;
                    ret = 1;
                }
            }
        }
        delete[] op1;
        delete[] op2;
        return ret;    
    }
public:    
    //����������� �� ���������.
    DynStr() {
        length = 1;
        stroka = new char;
        *stroka = '\0';
    }
    //����������� �� �������
    DynStr(unsigned int size) {
        length = size;
        stroka = new char[length + 1];
    }
    //����������� ����������� 
    DynStr(char* str1) {
        length = (unsigned int)strlen(str1);
        stroka = new char[length + 1];
        strcpy(stroka, str1);
    }
    //����������� �����������
    DynStr(char&& str1) {
        length = (unsigned int)strlen(&str1);
        stroka = new char[length + 1];
        strcpy(stroka, &str1);
    }
    //����������� ����������� �����������
    DynStr(const char* str1) {
        length = (unsigned int)strlen((char*)str1);
        stroka = new char[length + 1];
        strcpy(stroka, (char*)str1);
    }
    //����������� ����������� 
    DynStr(DynStr& d) {
        length = (unsigned int)strlen(d.stroka);
        stroka = new char[length + 1];
        strcpy(stroka, d.stroka);
    }
    //����������� ����������� �����������
    DynStr(const DynStr& d) {//cons3
        length = (unsigned int)strlen(d.stroka);
        stroka = new char[length + 1];
        strcpy(stroka, d.stroka);
    }
    //����������� �����������
    DynStr(DynStr&& dMove) {//cons4 like(probably) move- 
       length = (unsigned int)strlen(dMove.stroka);
       stroka = new char[length + 1];
       strcpy(stroka, dMove.stroka);
       dMove.~DynStr();
    }
    ~DynStr() {
        if (length>0) {
            delete[] this->stroka;
            length = 0;
        }
    }
    //�������� ������������ �����������
    DynStr& operator = (DynStr& d) {
        if (&d == this)
            return *this;
        if (stroka)
            delete[] this->stroka;
        this->length = d.length;
        this->stroka = new char[this->length+1];
        strcpy(this->stroka,d.stroka);
        return *this;
    }
    //�������� ������������ �����������
    DynStr& operator = (char* d) {
        if (d == this->GetStr())
            return *this;
        if (stroka)
            delete[] this->stroka;
        this->length = strlen(d);
        this->stroka = new char[this->length+1];
        strcpy(this->stroka, d);
        return *this;
    }
    //�������� ������������ �����������
    DynStr& operator = (DynStr&& dMove) {
        if (&dMove == this)
            return *this;
        if (stroka)
            delete[] this->stroka;
        this->length = dMove.length;
        this->stroka = new char[this->length+1];
        strcpy(this->stroka, dMove.stroka);
        dMove.~DynStr();
        return *this;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this < d1
    bool operator < (const DynStr d1) const {
        int ret = LEG(this->stroka,d1.stroka);
        if (ret == -1)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this > d1
    bool operator > (const DynStr d1) const {
        int ret = LEG(this->stroka, d1.stroka);
        if (ret == 1)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this >= d1
    bool operator >= (const DynStr d1) const {
        int ret = LEG(this->stroka, d1.stroka);
        if (ret >=0)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this <= d1
    bool operator <= (const DynStr d1)  const {
        int ret = LEG(this->stroka, d1.stroka);
        if (ret <= 0)
            return true;
        return false;
    }
    //���������� ������ ������� �� ������
    //���������� ����������� ������� LEG()
    //this == d1
    bool operator == (const DynStr d1) const {
        int ret = LEG(this->stroka, d1.stroka);
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
    friend DynStr operator + (const DynStr& d1, const DynStr& d2);
    friend DynStr operator + (const DynStr& d1, const char* d2);
    friend DynStr operator + (const char* d1, const DynStr& d2);
    friend DynStr operator + (const DynStr& d1, char* d2);
    friend DynStr operator + (char* d1, const DynStr& d2);

    //������� ���������� ������
    const char* GetStr() {
        return stroka;
    };
    //����������� ������� ��� ����������� �����.��������� �� ���� ��� ������ ��������.
    //�� ���� Less,Equal,Great
    //���������� -1, ���� ������ ������ ������ ������ �� ��������(������������������), 0 - �����, 1 - ������ ������ ������ �� ��������
    static int LEG(const char* str1, const char* str2) {
        return LEG((char*)str1,(char*)str2);
    }
};

DynStr operator + (const DynStr& d1, const DynStr& d2) {
    char* strRet = new char[d1.length + d2.length + 1];
    DynStr::strcpy(strRet, d1.stroka);
    DynStr::strcat(strRet, d2.stroka);
    DynStr ret(strRet);
    delete[] strRet;
    return ret;
};
DynStr operator + (const DynStr& d1, const char* d2) {
    return d1 + DynStr(d2);
};
DynStr operator + (const char* d1, const DynStr& d2) {
    return DynStr(d1) + d2;
};
DynStr operator + (const DynStr& d1, char* d2) {
    return d1 + DynStr(d2);
};
DynStr operator + (char* d1, const DynStr& d2) {
    return DynStr(d1) + d2;
};
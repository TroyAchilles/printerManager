#pragma once

/**
 * @brief 打印机的最小打印单元
 */
class PrintPage
{
    public:
        PrintPage() : _flag(false) { }
        PrintPage(bool flag) : _flag(flag) { }
        operator bool() { return _flag;}
    private:
        bool 	_flag;
};

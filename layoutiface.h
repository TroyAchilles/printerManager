#pragma once
#include "printpage.h"
#include "pt.h"

/**
 * @brief 打印机布局器接口，排版数据后生成PrintPage
 */
class LayoutIFace
{
    public:
        /**
         * @brief next, 在打印机控制流程中被循环调用生成打印页
         * @param page， 传出参数，传出产生的打印页
         * @return 返回布局的状态:
         * 			PT_ENDED表示布局完成
         * 			PT_WAITTING表示在阻塞
         * 			PT_EXIT表示退出
         * 			PT_YIELED让出控制权，下次直接从让出点继续执行
         * 注：如果内部使用pth的接口，请不要显式return,如果不使用pth接口，请忽略此规则
         * 新手建议使用switch case状态机实现
         */
        virtual pt_status next(PrintPage* page) = 0;

    public:
        LayoutIFace() : _isValid(false) { }
        virtual ~LayoutIFace() = default;
        operator bool() { return _isValid; }
    private:
        bool 		_isValid;
};



class SummaryLayout : public LayoutIFace
{
    public:
        SummaryLayout(){ PT_INIT(&_pt);}

        pt_status next(PrintPage *page)
        {
            PT_BEGIN(&_pt);

            *page = build_header();
            PT_YIELD(&_pt);

            *page = build_body();
            PT_YIELD(&_pt);

            *page = build_end();
            PT_END(&_pt);
        }

    private:
        PrintPage build_header()
        {
            qDebug() << "build_header()";
            return PrintPage(true);
        }

        PrintPage build_body()
        {
            qDebug() << "build_bodye() = ";
            return PrintPage(true);
        }

        PrintPage build_end()
        {
            qDebug() << "build_end()";
            return PrintPage(true);
        }

    private:
        struct pt 	_pt;
};

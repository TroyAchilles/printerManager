#include <QCoreApplication>
#include <QDebug>
#include "layoutiface.h"

/**
 * @brief 打印机任务，由manager管理
 */
class Content
{
    public:
        PrintPage page;
        LayoutIFace* layout;
};

class Device
{
    public:
        void print(PrintPage page) {Q_UNUSED(page)}
};

class PrinterManager
{
    public:
        void requesetPrint(PrintPage page) { Q_UNUSED(page) }
        void requesetPrint(LayoutIFace* layout)
        {
            Content ctx;
            ctx.layout = layout;
            _contenlist.append(ctx);
        }

        void threadRun()
        {
            auto ctx = _contenlist.takeFirst();

            if (ctx.page)
                _dev.print(ctx.page);

            if (ctx.layout)
            {
                PrintPage page;
                while(ctx.layout->next(&page) != PT_ENDED)
                        _dev.print(page);
            }
            qDebug() << "print over....";
        }

    private:
        QList<Content> 	_contenlist;
        Device 			_dev;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PrinterManager  mag;
    SummaryLayout sl;
    mag.requesetPrint(&sl);
    mag.threadRun();

    return a.exec();
}

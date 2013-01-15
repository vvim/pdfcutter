#include "pagerangelistwidgetitem.h"

PageRangeListWidgetItem::PageRangeListWidgetItem() : QListWidgetItem()
{
    start=0;
    end=0;
}

int PageRangeListWidgetItem::getPageRangeStart_int()
{
    return start;
}

QString PageRangeListWidgetItem::getPageRangeStart_qstring()
{
    QString ret;
    return ret.setNum(start);
}

int PageRangeListWidgetItem::getPageRangeEnd_int()
{
    return end;
}

QString PageRangeListWidgetItem::getPageRangeEnd_qstring()
{
    QString ret;
    return ret.setNum(end);
}

void PageRangeListWidgetItem::setPageRangeStart(int pagerangestart)
{
    start = pagerangestart;
    setData( LIST_ITEM_DATA_START ,pagerangestart);
}

void PageRangeListWidgetItem::setPageRangeEnd(int pagerangeend)
{
    end = pagerangeend;
    setData( LIST_ITEM_DATA_END ,pagerangeend);
}

QString PageRangeListWidgetItem::getPDFtkPageRange(QString param)
{
    return QString(param + getPageRangeStart_qstring() + "-" + getPageRangeEnd_qstring());
}

void PageRangeListWidgetItem::setChapterNaming(chapternaming cn)
{
    chaptername = cn;
}

QString PageRangeListWidgetItem::getNameBookTitle()
{
    return chaptername.booktitle;
}

QString PageRangeListWidgetItem::getNameStudentLevel()
{
    return chaptername.studentlevel;
}

QString PageRangeListWidgetItem::getNameChapter()
{
    return chaptername.chapter;
}

QString PageRangeListWidgetItem::getNameManualType()
{
    return chaptername.manualtype;
}

QString PageRangeListWidgetItem::getNamePagerange()
{
    return chaptername.pagerange;
}

int PageRangeListWidgetItem::getPagerangeStart()
{
    /*
    if ui->NamePageRange->text() is of the type p<int>-<int>
            return <int>
    else
    */
    return chaptername.pagerange_start;
}

int PageRangeListWidgetItem::getPagerangeEnd()
{
    /*
    if ui->NamePageRange->text() is of the type p<int>-<int>
            return <int>
    else
    */
    return chaptername.pagerange_end;
}

QString PageRangeListWidgetItem::getChaptertoString()
{
    return chaptername.booktitle + " " + chaptername.studentlevel + " " + chaptername.manualtype + " " + chaptername.chapter + " " + chaptername.pagerange;
}

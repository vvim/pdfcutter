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

#ifndef PAGERANGELISTWIDGETITEM_H
#define PAGERANGELISTWIDGETITEM_H


#define LIST_ITEM_DATA_START 1000
#define LIST_ITEM_DATA_END 1001

#include <QListWidgetItem>

class PageRangeListWidgetItem : public QListWidgetItem
{
public:
    PageRangeListWidgetItem();

    int getPageRangeStart_int();
    QString getPageRangeStart_qstring();
    int getPageRangeEnd_int();
    QString getPageRangeEnd_qstring();

    QString getPDFtkPageRange(QString param = "A");

    void setPageRangeStart(int pagerangestart);
    void setPageRangeEnd(int pagerangeend);

private:
    virtual bool operator<(const QListWidgetItem &other) const{
        if (data( LIST_ITEM_DATA_START ).toInt() == other.data( LIST_ITEM_DATA_START ).toInt())
            return data( LIST_ITEM_DATA_END ).toInt() < other.data( LIST_ITEM_DATA_END ).toInt();
        return data( LIST_ITEM_DATA_START ).toInt() < other.data( LIST_ITEM_DATA_START ).toInt();
    }

    int start, end;
};

#endif // PAGERANGELISTWIDGETITEM_H

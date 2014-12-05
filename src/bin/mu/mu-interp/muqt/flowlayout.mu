use qt;

documentation: """
Translated from the qt example code for a flow layout.

Since QStyle is not yet working, there are no optional values for spacing
-- they all need to be specified.
""";

class: FlowLayout : QLayout
{
    QLayoutItem[] itemList;
    int m_hSpace;
    int m_vSpace;

    method: FlowLayout (FlowLayout; QWidget parent) 
    { 
        QLayout.QLayout(this, parent); 
        itemList = QLayoutItem[]();
        let spacing = 15;
        m_hSpace = spacing;
        m_vSpace = spacing;
        setContentsMargins(spacing, spacing, spacing, spacing);
    }

    method: addItem (void; QLayoutItem item) { itemList.push_back(item); }
    method: horizontalSpacing (int;) { m_hSpace; }
    method: verticalSpacing (int;) { m_vSpace; }
    method: expandingDirections (Qt.Orientation;) { 0; }
    method: hasHeightForWidth (bool;) { true; }
    method: heightForWidth (int; int width) { doLayout(QRect(0, 0, width, 0), true); }
    method: count (int;) { itemList.size(); }
    method: itemAt (QLayoutItem; int index) { if index < itemList.size() then itemList[index] else nil; }
    method: sizeHint(QSize;) { minimumSize(); }

    method: minimumSize (QSize;) 
    {
        QSize size = QSize();

        for_each (item; itemList)
            size = size.expandedTo(item.minimumSize());

        return QSize(size.width() + 2 * margin(),
                     size.height() + 2 * margin());
    }

    method: setGeometry (void; QRect rect)
    {
        QLayout.setGeometry(this, rect);
        doLayout(rect, false);
    }

    method: takeAt (QLayoutItem; int index)
    {
        if index >= 0 && index < itemList.size()
            then itemList[index]
            else nil;
    }

    method: doLayout (int; QRect rect, bool testOnly)
    {
        let margins       = contentsMargins(),
            left          = margins.left(),
            right         = margins.right(),
            top           = margins.top(),
            bottom        = margins.bottom(),
            effectiveRect = rect.adjusted(left, top, -right, -bottom);

        int x = effectiveRect.x();
        int y = effectiveRect.y();
        int lineHeight = 0;

        for_each (item; itemList) 
        {
            let wid    = item.widget(),
                spaceX = horizontalSpacing(),
                spaceY = verticalSpacing();

            int nextX = x + item.sizeHint().width() + spaceX;

            if ((nextX - spaceX) > effectiveRect.right() && lineHeight > 0) 
            {
                x = effectiveRect.x();
                y = y + lineHeight + spaceY;
                nextX = x + item.sizeHint().width() + spaceX;
                lineHeight = 0;
            }
            
            if (!testOnly)
                item.setGeometry(QRect(QPoint(x, y), item.sizeHint()));

            x = nextX;
            lineHeight = math.max(lineHeight, item.sizeHint().height());
        }

        return y + lineHeight - rect.y() + bottom;
    }

}


\: clicked (void; bool checked, int num)
{
    print("CLICKED BUTTON %d -- OK BYE\n" % num);
    QCoreApplication.exit(0);
}



\: main ()
{
    let app     = QApplication(string[] {"qtest.mu"}),
        window  = QWidget(nil, Qt.Window),
        layout  = FlowLayout(window);

    let labels = string[] {"Short",
            "Longer",
            "Different text",
            "More text",
            "Even longer button text"};

    for (int i = 0; i < labels.size(); i++)
    {
        let button = QPushButton(labels[i], window);
        layout.addWidget(button);
        connect(button, QPushButton.clicked, clicked(,i));
    }

    window.show();
    window.raise();
    QApplication.exec();
}

main();

use qt;

\: clicked (void; bool checked)
{
    print("OK BYE\n");
    QCoreApplication.exit(0);
}

\: main ()
{
    let app    = QApplication(string[] {"qtest.mu"}),
        window = QWidget(nil, Qt.Window),
        hbox    = QHBoxLayout(window),
        tree   = QTreeWidget(window);

    hbox.addWidget(tree);
    QTreeWidgetItem[] items;

    for_each (text; ["one", "two", "three"])
    {
        let item = QTreeWidgetItem(string[]{text}, QTreeWidgetItem.Type),
            child = QTreeWidgetItem(string[]{"child"}, QTreeWidgetItem.Type),
            button = QPushButton(text, window);

        item.addChild(child);
        items.push_back(item);
        tree.addTopLevelItem(item);

        tree.setItemWidget(child, 0, button);
        connect(button, QPushButton.clicked, clicked);
    }

    let item = QTreeWidgetItem(string[] {"ui file"}, QTreeWidgetItem.Type),
        child = QTreeWidgetItem(string[] {"the ui file"}, QTreeWidgetItem.Type);

    QWidget top = loadUIFile("muqt/indexwidget.ui", nil);

    top.setAutoFillBackground(true);
    item.addChild(child);
    tree.addTopLevelItem(item);
    tree.setItemWidget(child, 0, top);
    tree.setIndentation(8);

    window.show();
    window.raise();
    QApplication.exec();
}

main();

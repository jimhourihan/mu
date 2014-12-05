use qt;

class: MyWidget : QWidget
{
    method: MyWidget (MyWidget; QObject parent, int windowFlags)
    {
        //
        // REQUIRED: call base constructor to build Qt native object
        //

        QWidget.QWidget(this, parent, windowFlags); 
        setAcceptDrops(true);  // FIX THIS
    }

    method: dragEnterEvent (void; QDragEnterEvent event)
    {
        print("drop enter\n");
        event.acceptProposedAction();
    }

    method: dropEvent (void; QDropEvent event)
    {
        print("drop\n");
        let mimeData = event.mimeData(),
            formats = mimeData.formats();

        print("--formats--\n");
        for_each (f; formats) print("%s\n" % f);

        if (mimeData.hasUrls())
        {
            print("--urls--\n");
            for_each (u; event.mimeData().urls()) print("%s\n" % u.toString(QUrl.None));
        }

        if (mimeData.hasText())
        {
            print("--text--\n");
            print("%s\n" % mimeData.text());
        }

        event.acceptProposedAction();
    }
}

\: clicked (void; bool checked)
{
    print("OK BYE\n");
    QCoreApplication.exit(0);
}

\: main ()
{
    let app    = QApplication(string[] {"qtest.mu"}),
        window = MyWidget(nil, Qt.Window),
        button = QPushButton("QUIT", window);

    connect(button, QPushButton.clicked, clicked);

    window.setSize(QSize(200, 200));
    window.show();
    window.raise();
    QApplication.exec();
}

main();


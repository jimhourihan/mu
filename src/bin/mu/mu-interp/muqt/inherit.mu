use qt;

class: MyWidget : QWidget
{
    method: MyWidget (MyWidget; QObject parent, int windowFlags)
    {
        //
        // REQUIRED: call base constructor to build Qt native object
        //

        QWidget.QWidget(this, parent, windowFlags); 
    }

    method: resizeEvent (void; QResizeEvent event)
    {
        print("resized\n");
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
        button = QPushButton("Resize the window", window);

    connect(button, QPushButton.clicked, clicked);

    window.setSize(QSize(200, 50));
    window.show();
    window.raise();
    QApplication.exec();
}

main();


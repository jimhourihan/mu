use qt;

\: clicked (void; bool checked, int num)
{
    print("CLICKED BUTTON %d -- OK BYE\n" % num);
    QCoreApplication.exit(0);
}

\: main ()
{
    let app     = QApplication(string[] {"qtest.mu"}),
        window  = QWidget(nil, Qt.Window),
        hbox    = QHBoxLayout(window);

    for (int i = 0; i < 10; i++)
    {
        let button = QPushButton(string(i), window);
        hbox.addWidget(button);
        connect(button, QPushButton.clicked, clicked(,i));
    }

    window.show();
    window.raise();
    QApplication.exec();
}

main();

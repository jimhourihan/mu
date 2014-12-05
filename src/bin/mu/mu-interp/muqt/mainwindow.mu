use qt;
use io;

\: open (void; bool clicked, QWidget parent, QPlainTextEdit textedit)
{
    let dialog = QFileDialog(parent, "Open a File to Edit", ".", "");
        
    if (dialog.exec() == 1) 
    {
        ifstream file = ifstream(dialog.selectedFiles().front());
        let text = read_all(file);
        file.close();
        textedit.setPlainText(text); 
    }
}

\: quit (void; bool checked)
{
    print("OK BYE\n");
    QCoreApplication.exit(0);
}

\: main ()
{
    let app      = QApplication(string[] {"qtest.mu"}),
        window   = QMainWindow(nil, Qt.Window),
        menubar  = QMenuBar(nil), //window.menuBar(),
        file     = menubar.addMenu("File"),
        toolbar  = window.addToolBar("MainStuff"),
        openAct  = file.addAction("Open..."),
        saveAct  = file.addAction("Save As..."),
        closeAct = file.addAction("Close"),
        textedit = QPlainTextEdit(window),
        status   = window.statusBar();

    toolbar.addAction(openAct);
    toolbar.addAction(saveAct);
    toolbar.addAction(closeAct);
    window.setCentralWidget(textedit);
    window.setUnifiedTitleAndToolBarOnMac(true);

    textedit.setStyleSheet("QPlainTextEdit { font-family: \"Monaco\"; background-color: rgb(230,230,230); }");
    textedit.setLineWrapMode(QPlainTextEdit.NoWrap);

    openAct.setShortcut(QKeySequence("Ctrl+o"));
    closeAct.setShortcut(QKeySequence("Ctrl+w"));

    connect(openAct, QAction.triggered, open(,window,textedit));
    connect(closeAct, QAction.triggered, quit);

    window.setSize(QSize(500, 300));
    window.show();
    window.raise();
    QApplication.exec();
}

main();

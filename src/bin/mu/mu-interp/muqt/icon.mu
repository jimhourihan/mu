use qt;

\: clicked (void; bool checked)
{
    print("OK BYE\n");
    QCoreApplication.exit(0);
}

\: main ()
{
    let app    = QApplication(string[] {"icon.mu"}),
        window = QWidget(nil, Qt.Window),
        image  = QImage("muqt/new_48x48.png", nil);

    image.invertPixels(QImage.InvertRgb);

    let pixmap = QPixmap.fromImage(image, Qt.AutoColor),
        icon   = QIcon(pixmap),
        button = QPushButton(icon, "MuQt: HELLO WORLD!", window);
    
    connect(button, QPushButton.clicked, clicked);

    window.setSize(QSize(200, 50));
    window.show();
    window.raise();
    QApplication.exec();
}

main();

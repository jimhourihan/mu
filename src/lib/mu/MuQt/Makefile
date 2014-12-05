#  -*- mode: makefile -*-

PROJECT     = MuQt
TYPE        = LIBRARY

AUTOTYPES     = Color Size Point PointF Rect RectF Font KeySequence \
	      Icon Pixmap Bitmap Region Variant Url DateTime Time Date \
	      ByteArray ModelIndex Object LayoutItem PaintDevice Image \
	      RegExp TextCursor TextOption TextBlock \
              Widget Layout Margins Clipboard \
	      BoxLayout FormLayout GridLayout StackedLayout \
	      HBoxLayout VBoxLayout \
              DockWidget WebView ToolBar \
              MainWindow WebPage WebFrame Action ActionGroup Slider Dial \
              LineEdit Frame AbstractSlider AbstractButton \
              CheckBox PushButton RadioButton ToolButton ButtonGroup \
              Menu ComboBox Completer SvgWidget FileDialog \
	      AbstractItemModel AbstractListModel AbstractTableModel \
	      StandardItemModel AbstractItemView ColorDialog Dialog \
	      StandardItem ListWidgetItem TreeWidgetItem TableWidgetItem \
	      ColumnView HeaderView ListView TableView TreeView \
	      ListWidget TreeWidget \
              TableWidget CoreApplication Application \
	      Label MenuBar PlainTextEdit ProgressBar \
	      ScrollArea SpinBox Splitter StackedWidget StatusBar \
	      TabBar TabWidget TextDocument TextEdit ToolBox \
              WidgetAction AbstractSpinBox AbstractScrollArea \
	      InputDialog EventLoop GroupBox \
	      NetworkReply Timer \
	      IODevice Process ProcessEnvironment \
	      File FileInfo Dir AbstractSocket TcpSocket \
	      UdpSocket TcpServer HostAddress HostInfo LocalSocket \
	      DesktopWidget \
	      ItemSelectionRange ItemSelection ItemSelectionModel \
	      Gradient Brush Matrix Transform ConicalGradient \
	      LinearGradient RadialGradient Palette \
              SpacerItem WidgetItem MimeData \
	      Event ResizeEvent DragLeaveEvent DragMoveEvent DropEvent \
	      InputEvent MoveEvent PaintEvent ShortcutEvent ShowEvent \
	      TimerEvent FocusEvent GestureEvent FileOpenEvent CloseEvent \
	      DragEnterEvent HideEvent HoverEvent HelpEvent \
	      ContextMenuEvent KeyEvent MouseEvent TabletEvent \
	      WheelEvent WindowStateChangeEvent \
	      TextStream TextCodec TextBrowser \
	      NetworkCookieJar NetworkCookie WebSettings \
	      NetworkAccessManager Cursor
	      #
	      #  NetworkAccessManager has been modified to us an RVNetworkAccessManager
	      #  instead of a QNetworkAccessManager, so if the generation script is run again
	      #  the files QNetworkAccessManagerType.* must be modified accordingly.
	      #

	      #Painter PainterPath



MANUALTYPES = QtColorTriangle

CXXFILES    = qtModule Bridge qtUtils qtGlobals \
              $(addsuffix Type,$(addprefix Q,$(AUTOTYPES))) \
              $(addsuffix Type,$(MANUALTYPES)) \
              SignalSpy

# Qt developers are being sloppy in their includes
# QtWebKit assumes that QtCore's headers are in the path
IPATH       = /usr/include \
              /Library/Frameworks/QtCore.framework/Headers/ \
              $(QTDIR)/include/QtCore \
	      /usr/include/qt4/QtCore\

QTFILES     = qtcolortriangle RvNetworkAccessManager

GENFILES    = $(metasrc_dir)/$(MOCPREFIX)SignalSpy_filtered.hpp

FRAMEWORKS_DARWIN  = QtCore QtOpenGL QtGui QtWebKit OpenGL System IOKit \
                     Foundation AppKit Carbon Quicktime CoreAudio

LIBS        = MuLang Mu gc

noincludegoals += translate
include $(SRC_ROOT)/build/Makefile.master


$(metasrc_dir)/$(MOCPREFIX)SignalSpy_filtered.hpp: $(metasrc_dir)/$(MOCPREFIX)SignalSpy.cpp
	$(MKDIR) $(dir $@) ; sed -f signalspy.sed $^ > $@

.PHONY: translate
translate:
	./qt2mu.py -v -o $(addprefix Q,$(AUTOTYPES))
	./qt2mu.py -module $(addprefix Q,$(AUTOTYPES))

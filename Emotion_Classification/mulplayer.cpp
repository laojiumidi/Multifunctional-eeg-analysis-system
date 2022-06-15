#include "test_film.h"
#include "ui_mulplayer.h"

MulPlayer::MulPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MulPlayer),
    m_playerState(QMediaPlayer::StoppedState)
{
    ui->setupUi(this);

    //MainWindow自带layout，所以需要自定义layout并把它设置成中心layout
    //否则将会出现不能设置layout错误
    QWidget *widget = new QWidget;
    this->setCentralWidget(widget);

    player = new QMediaPlayer;

    Playlist = new QMediaPlaylist();
    player->setPlaylist(Playlist);

    videoWidget = new QVideoWidget(widget);
    player->setVideoOutput(videoWidget);
    ui->progressBar->setRange(0, player->duration() / 1000);

    //水平布局，控制按钮
    QBoxLayout *ctlLayout = new QHBoxLayout;
    ctlLayout->addWidget(ui->openFileBtn);
    ctlLayout->addWidget(ui->playBtn);
    ctlLayout->addWidget(ui->stopBtn);
    ctlLayout->addWidget(ui->fullScrBtn);
    ctlLayout->addWidget(ui->home);

    //垂直布局：视频播放器、进度条、控制按钮布局
    QBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(videoWidget);
    mainLayout->addWidget(ui->progressBar);
    mainLayout->addLayout(ctlLayout);

    //设置布局
    widget->setLayout(mainLayout);


    //信号槽
    QObject::connect(ui->openFileBtn,SIGNAL(clicked()),this,SLOT(openFile()));
    QObject::connect(ui->playBtn,SIGNAL(clicked()),this,SLOT(playVideo()));
    QObject::connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(stopVideo()));
    QObject::connect(ui->fullScrBtn,SIGNAL(clicked()),this,SLOT(fullScr()));
    QObject::connect(ui->home,SIGNAL(clicked()),this,SLOT(back_to_teststart()));
}

MulPlayer::~MulPlayer()
{
    delete ui;
}

void MulPlayer::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"));
    addToPlaylist(fileNames);
}

void MulPlayer::playVideo()
{
    m_playerState = QMediaPlayer::PlayingState;
    player->play();
}

void MulPlayer::stopVideo()
{
    m_playerState = QMediaPlayer::StoppedState;
    player->stop();
}

void MulPlayer::fullScr()
{
    if(m_playerState == QMediaPlayer::PlayingState)
    {
        videoWidget->setFullScreen(true);
    }
    else
    {
        videoWidget->setFullScreen(false);
    }

}

void MulPlayer::addToPlaylist(const QStringList& fileNames)
{
    foreach (QString const &argument, fileNames) {
        QFileInfo fileInfo(argument);
        if (fileInfo.exists()) {
            QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            if (fileInfo.suffix().toLower() == QLatin1String("m3u")) {
                Playlist->load(url);
            } else
                Playlist->addMedia(url);
        } else {
            QUrl url(argument);
            if (url.isValid()) {
                Playlist->addMedia(url);
            }
        }
    }
}

void MulPlayer::back_to_teststart()
{
    emit back_teststart(true);
    MulPlayer::hide();
}

//void MulPlayer::mp_show(bool corr)
//{
//    if(corr)
//        MulPlayer::show();
//}

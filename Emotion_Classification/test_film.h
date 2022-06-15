//头文件
#ifndef MULPLAYER_H
#define MULPLAYER_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QBoxLayout>

namespace Ui {
class MulPlayer;
}

class MulPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MulPlayer(QWidget *parent = 0);
    ~MulPlayer();
    void addToPlaylist(const QStringList& fileNames);
private:
    Ui::MulPlayer *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *Playlist;
    QString m_fileName;
    QMediaPlayer::State  m_playerState;
signals:
    void back_teststart(bool corr);
public slots:
    void back_to_teststart();
    void openFile();
    void playVideo();
    void stopVideo();
    void fullScr();
};

#endif // MULPLAYER_H

#include "downloadqueuecache.h"
#include "downloadnetworkthread.h"

#include <QStringList>

DownloadQueueCache::DownloadQueueCache(Download_Type type, QObject *parent)
    : DownloadQueueCache(DownloadQueueData(), type, parent)
{

}

DownloadQueueCache::DownloadQueueCache(const DownloadQueueData &data, Download_Type type, QObject *parent)
    : DownLoadThreadAbstract(data.m_url, data.m_savePath, type, parent)
{
    m_request = nullptr;
    m_isDownload = false;
    m_isAbort = false;

    m_manager = new QNetworkAccessManager(this);
    m_request = new QNetworkRequest();
#ifndef QT_NO_SSL
    connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                       SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
    M_LOGGER_INFO(QString("%1 Support ssl: %2").arg(getClassName()).arg(QSslSocket::supportsSsl()));

    QSslConfiguration sslConfig = m_request->sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_request->setSslConfiguration(sslConfig);
#endif
}

DownloadQueueCache::DownloadQueueCache(const DownloadQueueDatas &datas, Download_Type type, QObject *parent)
    : DownloadQueueCache(DownloadQueueData(), type, parent)
{
    addImageQueue(datas);
}

DownloadQueueCache::~DownloadQueueCache()
{
    if(m_request)
    {
        delete m_request;
        m_request = nullptr;
    }
    deleteAll();
}

QString DownloadQueueCache::getClassName()
{
    return staticMetaObject.className();
}

void DownloadQueueCache::startToDownload()
{
    if(!m_imageQueue.isEmpty())
    {
        startOrderImageQueue();
    }
}

void DownloadQueueCache::abort()
{
    if(m_isDownload && m_reply)
    {
        m_isAbort = true;
        m_reply->abort();
        m_file->close();
        m_file->remove();
        delete m_reply;
        m_reply = nullptr;
        m_isAbort = false;
    }
}

void DownloadQueueCache::addImageQueue(const DownloadQueueDatas &datas)
{
    m_imageQueue = datas;
}

void DownloadQueueCache::startOrderImageQueue()
{
    if(!m_imageQueue.isEmpty() && M_NETWORK_PTR->isOnline())
    {
        if(QFile::exists(m_imageQueue.first().m_savePath))
        {
            emit downLoadDataChanged(m_imageQueue.takeFirst().m_savePath);
            startOrderImageQueue();
        }
        else
        {
            startDownload(m_imageQueue.first().m_url);
        }
    }
}

void DownloadQueueCache::startDownload(const QString &url)
{
    m_isDownload = true;
    delete m_file;
    m_file = new QFile( m_imageQueue.first().m_savePath, this);
    if(!m_file->open(QFile::WriteOnly))
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
        return;
    }

    if(!m_request || !m_manager)
    {
        return;
    }

    m_timer.start(MT_S2MS);
    m_request->setUrl(QUrl(url));
    m_reply = m_manager->get(*m_request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(readyReadSlot()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
}

void DownloadQueueCache::downLoadFinished()
{
    if(m_isAbort || !m_request || !m_manager || !m_reply || !m_file)
    {
        return;
    }
    m_timer.stop();

    m_file->flush();
    m_file->close();
    m_reply->deleteLater();
    m_reply = nullptr;
    m_isDownload = false;
    emit downLoadDataChanged(m_imageQueue.takeFirst().m_savePath);

    startOrderImageQueue();
}

void DownloadQueueCache::readyReadSlot()
{
    if(!m_file || !m_reply)
    {
        return;
    }

    m_file->write(m_reply->readAll());
    m_file->flush();
}

void DownloadQueueCache::errorSlot(QNetworkReply::NetworkError code)
{
    if(!m_file || !m_reply)
    {
        return;
    }
#ifndef DOWNLOAD_DEBUG
    Q_UNUSED(code);
#endif
    M_LOGGER_ERROR(QString("QNetworkReply::NetworkError : %1 %2").arg(code).arg(m_reply->errorString()));
    m_file->flush();
    if(!m_isAbort)
    {
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}
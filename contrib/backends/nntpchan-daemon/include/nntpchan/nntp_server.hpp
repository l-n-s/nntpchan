#ifndef NNTPCHAN_NNTP_SERVER_HPP
#define NNTPCHAN_NNTP_SERVER_HPP
#include "frontend.hpp"
#include "server.hpp"
#include <deque>
#include <string>
#include <uv.h>

namespace nntpchan
{

class NNTPServer : public Server
{
public:
  NNTPServer(uv_loop_t *loop);

  virtual ~NNTPServer();

  void SetStoragePath(const std::string &path);

  void SetLoginDB(const std::string path);

  void SetInstanceName(const std::string &name);

  std::string InstanceName() const;

  void Close();

  virtual IServerConn *CreateConn(uv_stream_t *s);

  virtual void OnAcceptError(int status);

  void SetFrontend(Frontend *f);

private:
  std::string m_logindbpath;
  std::string m_storagePath;
  std::string m_servername;

  Frontend_ptr m_frontend;
};

class NNTPServerConn : public IServerConn
{
public:
  NNTPServerConn(uv_loop_t *l, uv_stream_t *s, Server *parent, IConnHandler *h) : IServerConn(l, s, parent, h) {}

  virtual bool IsTimedOut() { return false; };

  /** @brief send next queued reply */
  virtual void SendNextReply();

  virtual void Greet();
};
}

#endif

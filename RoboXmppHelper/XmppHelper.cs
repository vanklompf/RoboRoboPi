using Sharp.Xmpp;
using Sharp.Xmpp.Client;

namespace RoboXmppHelper
{
  public static class XmppHelper
  {
    private static readonly Jid Jid = "robo@xmppeval.cloudapp.net";

    public static bool SendCommand(string command)
    {
      using (var client = new XmppClient("xmppeval.cloudapp.net", "webazure", "abcd"))
      {
        client.Connect();
        client.SendMessage(Jid, command);
      }

      return true;
    }
  }
}

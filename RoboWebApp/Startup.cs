using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(RoboWebApp.Startup))]
namespace RoboWebApp
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}

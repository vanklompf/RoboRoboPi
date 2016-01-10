using System;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;

namespace AndroidRoboRobo
{
  [Activity(Label = "AndroidRoboRobo", MainLauncher = true, Icon = "@drawable/icon")]
  public class MainActivity : Activity
  {
    int _count = 1;

    protected override void OnCreate(Bundle bundle)
    {
      base.OnCreate(bundle);

      // Set our view from the "main" layout resource
      SetContentView(Resource.Layout.Main);

      // Get our button from the layout resource,
      // and attach an event to it
      var helloButton = FindViewById<Button>(Resource.Id.MyButton);
      var connectButton = FindViewById<Button>(Resource.Id.ConnectButton);
      var bar = FindViewById<SeekBar>(Resource.Id.seekBar1);
      var value = FindViewById<EditText>(Resource.Id.editText1);

      helloButton.Click += delegate { helloButton.Text = $"{_count++} clicks!oneone!"; };
      connectButton.Click += delegate { connectButton.Text = "Connected"; };

      bar.ProgressChanged += delegate { value.Text = bar.Progress.ToString(); };
    }
  }
}


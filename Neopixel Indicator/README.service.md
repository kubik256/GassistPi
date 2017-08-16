#- Save google-assistant-demo.service file into:
`/etc/systemd/system/google-assistant-demo.service`

#- Reload daemon:
`systemctl daemon-reload`

#- Start GA service:
`systemctl start google-assistant`

#- Check service status for errors:
`systemctl status google-assistant`

#- Enable service startup
`systemctl enable google-assistant`

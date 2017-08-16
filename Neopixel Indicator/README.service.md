1) Save google-assistant-demo.service file into:
/etc/systemd/system/google-assistant-demo.service

2) Reload daemon:
systemctl daemon-reload

3) Start GA service:
systemctl start google-assistant

4) Check service status for errors:
systemctl status google-assistant

5) Enable service startup:
systemctl enable google-assistant

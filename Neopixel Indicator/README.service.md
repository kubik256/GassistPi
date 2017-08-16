## Save google-assistant-demo.service file into system folder

`/etc/systemd/system/google-assistant-demo.service`

```bash
sudo chown root:root /etc/systemd/system/google-assistant-demo.service
sudo chmod 644 /etc/systemd/system/google-assistant-demo.service
```

## Inicialize startup service

```bash
sudo systemctl enable google-assistant-demo.service
sudo systemctl start google-assistant-demo.service
```


# -*- coding: utf-8 -*-

import  tkinter as  tk
from tkinter import *
from tkinter import messagebox
from platform import python_version
import smtplib, cv2, os
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from twilio.rest import Client
import subprocess as sp
from datetime import datetime
global d
global c
c = str()
d = datetime.now()
c = "d"+str(d.day)+"m0"+str(d.month)

if(d.hour < 12):
	c = c +"tma"
if(d.hour >= 12 and d.hour < 19):
	c = c +"tta"
if(d.hour > 19):
	c = c +"tno"

data = str(datetime.now())

def main(args):

	root = tk.Tk()
	root.title("Security_Cam")
	root['bg']="#000000"
	root.geometry("500x400")

	lbl1= tk.Label(root, text="Posicione o ponteiro do mouse sobre a area vermelha\ne o Security_Cam vigiará sua residência\n\nDesenvolvedores: Daniel Cardoso, Daniel Martins, Kaio Prates", bg="#000000", fg="white")
	minhaTela = tk.Frame(root)
	minhaTela['bg'] = '#DC143C'


	lbl1.pack( padx= "10", pady="10")

	minhaTela.pack( padx= "10", pady="10",expand=3, fill="both")

	minhaTela.bind('<Button-3>',sms)



	tk.mainloop()

	return 0

def sms(event):
	dados  = open("file.db",'r')
	dados = dados.readlines()
	ip_dado = dados[0]
	account_sid = dados[1]
	auth_token  = dados[2]
	telefone = dados[3]
	telefone_twilio = dados[4]
	email_dado = dados[5]
	senha_dado = dados[6]
	status, ip = sp.getstatusoutput('ping -w 3 '+ip_dado)

	if(status == 1):
		msg= ("---------SMS---------")
		client = Client(account_sid, auth_token)
		text = str('Evento inesperado em {}'.format(data))
		message = client.messages.create(to=telefone,
			from_= telefone_twilio,
			body = text)
		messagebox.showinfo("Mensagem enviada", msg)
		msg= ("-----FOTO------");camera_port = 0
		nFrames = 30
		camera = cv2.VideoCapture(camera_port)
		file = "imagen.png"
		retval, img = camera.read()
		cv2.imshow('Foto',img)
		cv2.imwrite(file,img)
		cv2.destroyAllWindows()
		camera.release()
		messagebox.showinfo("Capturado", msg)
		os.system("./whale -a "+c+"fl1")
		msg= ("---------EMAIL---------");server = smtplib.SMTP('smtp.gmail.com:587')
		server.starttls()

		server.login(email_dado,senha_dado)

		to_addr = email_dado
		subject = 'SECURIT CAM EVENT'
		body = 'Essa pessoa invadiu sua residência'

		msg = MIMEMultipart()
		msg["From"] = email_dado
		msg["To"] = to_addr
		msg["Subject"] = subject

		imgFilename = 'imagen.png'
		with open('imagen.png', 'rb') as f:
			msgImg = MIMEImage(f.read(), name=imgFilename)
		msg.attach(msgImg)
		msgText = MIMEText('<b>{}</b><br><img src="cid:{}"><br>'.format(body, imgFilename), 'html')
		msg.attach(msgText)
		server.sendmail(email_dado, to_addr, msg.as_string())
		server.quit()
		messagebox.showinfo("Email enviado", msg)
	if(status == 0):
		msg = "O Alarme entrára em atividade\nassim que seu dispositivo móvel\nsair da rede"
		messagebox.showinfo("ALARME DESATIVADO", msg)
		os.system("./whale -a "+c+"fl0")

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))

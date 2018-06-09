
# -*- coding: utf-8 -*-
#Autor=_Kaiofprates_

import  tkinter as  tk
from tkinter import messagebox
from platform import python_version
import smtplib, cv2
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from twilio.rest import Client
from datetime import datetime

data = str(datetime.now())

def main(args):

	root = tk.Tk()
	root.title("Security_Cam")
	root['bg']="#8B008B"
	root.geometry("500x400")



	lbl1= tk.Label(root, text="Posicione o ponteiro do mouse sobre a area cinza\ne o Security_Cam vigiará sua residência\n\nDesenvolvedores: Daniel Cardoso, Daniel Martins, Kaio Prates", bg="#9400D3", fg="white")
	minhaTela = tk.Frame(root)


	lbl1.pack( padx= "10", pady="10")

	minhaTela.pack( padx= "10", pady="10",expand=3, fill="both")

	minhaTela.bind('<Button-1>',sms)
	minhaTela.bind('<Button-2>',foto)
	minhaTela.bind('<Button-3>',email)


	tk.mainloop()

	return 0

def sms(event):
	msg= ("---------SMS---------")
	account_sid = "#"
	auth_token  = "#"
	client = Client(account_sid, auth_token)
	text = str('Evento inesperado em {}'.format(data))
	message = client.messages.create(to="#",
		from_="#",
		body = text)
	messagebox.showinfo("Mensagem enviada", msg)

def foto(event):
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


def email(event):
	msg= ("---------EMAIL---------");server = smtplib.SMTP('smtp.gmail.com:587')
	server.starttls()
	server.login("email","senha")

	to_addr = 'remetente'
	subject = 'SECURITy CAM EVENT'
	body = 'Essa pessoa invadiu sua residência'

	msg = MIMEMultipart()
	msg["From"] = "email"
	msg["To"] = to_addr
	msg["Subject"] = subject

	imgFilename = 'imagen.png'
	with open('imagen.png', 'rb') as f:
		msgImg = MIMEImage(f.read(), name=imgFilename)
	msg.attach(msgImg)
	msgText = MIMEText('<b>{}</b><br><img src="cid:{}"><br>'.format(body, imgFilename), 'html')
	msg.attach(msgText)
	server.sendmail("email", to_addr, msg.as_string())
	server.quit()
	messagebox.showinfo("Email enviado", msg)

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))

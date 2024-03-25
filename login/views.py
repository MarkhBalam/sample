#from django.shortcuts import render
from django.shortcuts import redirect, render
from django.http import HttpResponse
from django.template import loader
from django.contrib.auth.models import User
from django.contrib import messages
from django.contrib.auth import authenticate,login,logout
from E_commerce import settings
from django.core.mail import send_mail
from django.contrib.sites.shortcuts import get_current_site
from django.template.loader import render_to_string
from django.utils.http import urlsafe_base64_encode, urlsafe_base64_decode
from django.utils.encoding import force_bytes , force_str
from .tokens import generate_token
from django.core.mail import send_mail, EmailMessage
from .models import business
# Create your views here.
def home(request):
    
    return render(request,'login/index.html')

def signup(request):
    if request.method == "POST":
        username = request.POST["username"]
        fname = request.POST["fname"]
        lname = request.POST['lname']
        email = request.POST['email']
        TIN = request.POST['TIN']
        type_business = request.POST['type_business']
        pass1 = request.POST['pass1']
        pass2 = request.POST['pass2']

        if User.objects.filter(username = username):
            messages.error(request,"Username already exist! Please try some other username")
            return redirect('home')
        
        if User.objects.filter(email=email):
            messages.error(request,"Email already registered")
            return redirect('home')
        
        if len(username)>13:
            messages.error(request,"Usernmae must be under 10 characters")

        if pass1 != pass2:
            messages.error(request,"Passwords didnt match!")

        if not username.isalnum():
            messages.error(request,"Username must be Alpha-Numeric!")
            return redirect("home")
        
        myuser = User.objects.create_user(username,email,pass1)
        myuser.first_name = fname
        myuser.last_name = lname
        myuser.is_active = False

        myuser.save()

        details = business(
        TIN = TIN,
        type_business = type_business
        )
        details.save()



        messages.success(request,"Your account has been successfull created.. We have sent you a confirmation email , please confirm your email in order to activate your email.")

        #welcome Email
        subject = "Welcome to G-10 , G-10 Login ! "
        message = "Hello" + myuser.first_name + "!! \n" +"Welcome to G-10 \n Thanks for visiting our websites..\n We have also sent a confirmation email , please confirm your email address inorder to activate your account. \n\n Thanking you.."
        from_email = settings.EMAIL_HOST_USER
        to_list = [myuser.email]
        send_mail(subject,message,from_email,to_list,fail_silently=True)
        # Email Address Confirmation Email

        current_site = get_current_site(request)
        email_subject = "Confirm your email"
        message2 = render_to_string('email_confirmation.html', {
            'name':myuser.first_name,
            'domain': current_site.domain,
            'uid' : urlsafe_base64_encode(force_bytes(myuser.pk)),
            'token':generate_token.make_token(myuser),
        })
        email = EmailMessage(
            subject=email_subject,
            body=message2,
            from_email=settings.EMAIL_HOST_USER,
            to=[myuser.email],
        )
        email.fail_silently  = True
        email.send()
        return redirect('signin')
    return render(request,"login/signup.html")   

def signin(request):

    if request.method == 'POST':
        username = request.POST['username']
        pass1 = request.POST['pass1']

        user = authenticate(username=username,password=pass1)

        if user is not None:
            login(request,user)
            fname = user.first_name
            #return render(request,'login/index.html',{'fname':fname})
            return redirect('homepage')
        else:
            print("Invalid Credentials")
            messages.error(request,"Bad credential")
            return redirect('home')
            
    
    return render(request,"login/signin.html")

def signout(request):
    
    logout(request)
    messages.success(request,"Logged Out Successful")
    return redirect('home')

def activate(request,uidb64,token):
    try:
        uid  = force_str(urlsafe_base64_decode(uidb64))
        myuser = User.objects.get(pk=uid)
    except (TypeError,ValueError,OverflowError,User.DoesNotExist): 
        myuser = None

    if myuser is not None and generate_token.check_token(myuser,token):
        myuser.is_active = True
        myuser.save()
        login(request , myuser)
        #return redirect('home')
        return redirect('homepage')
    else:
        return render(request,'activation_failed.html')
    
    # eanT7Ew=24bR+afm
from django.shortcuts import render

def business_login(request):
    return render(request, 'login.html')

from django.shortcuts import render

# Create your views here.
def my_account(request):
      return render(request, 'My_account/account.html' )
from django.shortcuts import render, HttpResponse

# Create your views here.
def help(request):
      return render(request, 'index.html')


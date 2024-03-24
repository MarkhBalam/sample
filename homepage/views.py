from django.shortcuts import render

def homepage(request):
    return render(request, 'homepage/index.html')

# def add_product(request):
#     return render(request, 'add_product.html')

# def order_status(request):
#     return render(request, 'order_status.html')

# def account(request):
#     return render(request, 'account.html')

# def help(request):
#     return render(request, 'help.html')

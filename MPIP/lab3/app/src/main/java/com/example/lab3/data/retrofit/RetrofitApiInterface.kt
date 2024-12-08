package com.example.lab3.data.retrofit

import com.example.lab3.data.Quote
import retrofit2.Call
import retrofit2.http.GET

interface RetrofitApiInterface {

    @GET("quotes")
    fun getQuotes(): Call<Quote>

}
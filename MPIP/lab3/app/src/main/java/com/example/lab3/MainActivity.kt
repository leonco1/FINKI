package com.example.lab3

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge
import com.example.lab3.data.Quote
import com.example.lab3.data.retrofit.RetrofitInstance
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        val call=RetrofitInstance.apiService.getQuotes()
        call.enqueue(object:Callback<Quote>{

            override fun onResponse(call: Call<Quote>, response: Response<Quote>) {
                if (response.isSuccessful)
                {
                    val quote=response.body()
                    System.out.println(quote)

                }
            }

            override fun onFailure(call: Call<Quote>, t: Throwable) {
                return
            }
        })

    }
}





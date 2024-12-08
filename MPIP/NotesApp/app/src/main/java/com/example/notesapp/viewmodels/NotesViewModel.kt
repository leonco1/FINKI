package com.example.notesapp.viewmodels

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.notesapp.data.Notes

class NotesViewModel :ViewModel(){

    private val _inputText:MutableLiveData<String>  by lazy { MutableLiveData<String>() }
    private val _notesList:MutableLiveData<MutableList<String>> by lazy{ MutableLiveData(mutableListOf())}

    fun getUserText():String
    {
        return _inputText.value.toString()
    }
    fun setUserText(text:String)
    {
        this._inputText.value=text
    }
//    fun submitText():String
//    {
//        val text=_inputText.value.toString()
//        _notesList.value?.add(text)
//        _notesList.value=_notesList.value
//        _inputText.value=""
//        return "Something"
//
//    }

    fun getUserTextValue():MutableLiveData<String>
    {
        return this._inputText
    }
}
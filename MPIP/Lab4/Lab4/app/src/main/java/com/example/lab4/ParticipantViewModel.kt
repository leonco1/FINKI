//package com.example.lab4
//
//import androidx.lifecycle.LiveData
//import androidx.lifecycle.MutableLiveData
//import androidx.lifecycle.ViewModel
//import kotlinx.coroutines.Dispatchers
//import kotlinx.coroutines.launch
//import androidx.lifecycle.viewModelScope
//
//
//class ParticipantViewModel(private val participantRepository: ParticipantRepository):ViewModel() {
//
//    private val participantLiveData=MutableLiveData<List<Participant>>()
//
//    fun getParticipantLiveData():LiveData<List<Participant>> = participantLiveData
//
//    fun listAll()
//    {
//        viewModelScope.launch(Dispatchers.IO)
//        {
//            val participants=participantRepository.listParticipants()
//            participantLiveData.postValue(participants)
//        }
//    }
//
//}
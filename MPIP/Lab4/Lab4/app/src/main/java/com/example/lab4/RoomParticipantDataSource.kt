package com.example.lab4

class RoomParticipantDataSource(private val participantDao:ParticipantDao):LocalParticipantDataSource {
    override suspend fun insertParticipant(participant: Participant) {
       participantDao.insertParticipant(participant)
    }

    override suspend fun deleteParticipant(participant: Participant) {

        participantDao.deleteParticipant(participant)
    }

    override suspend fun deleteParticipant(id: Int) {
        participantDao.deleteParticipant(id)
    }

    override suspend fun getAllParticipants(): List<Participant> {
        return participantDao.getAllParticipants()
    }
}